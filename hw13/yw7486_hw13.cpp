#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int WORLD_HEIGHT = 5, 
          WORLD_WIDTH = 5;
const int ANT_BREED_INTERVAL = 3,
          BUG_BREED_INTERVAL = 8,
          BUG_STARVE = 3;
const char EMPTY = '-',
           ANT = 'o',
           DOODLEBUG = 'X';

struct Position
{
    Position() : h(-1), w(-1) {}
    Position(int x, int y) : h(x), w(y) {}
    int h, w;
};


class Organism
{
public:
    Organism()
    : type(EMPTY), breed_interval(-1), position(-1, -1), moved(false) {}
    // Organism(Position pos)
    // : type(EMPTY), breed_interval(-1), position(pos) {}
    Organism(char type, int breed_interval, int h, int w) 
    : type(type), breed_interval(breed_interval), position(h, w), moved(false) {}

    friend ostream &operator<<(ostream &outs, const Organism &o) { 
        outs << o.type; return outs; }

    // int get_bread_interval() const { return breed_interval; }
    char get_type() { return type; }
    Position get_position() { return position; }
    bool has_moved() { return moved; }

    void set_position(int h, int w) { position.h = h; position.w = w; }
    void set_position(Position new_pos) { position = new_pos; }
    void set_moved(bool status) { moved = status; }

    vector<Position> get_target_positions(Organism*** world, int height, int width, char target) const;
    Position get_random_position(Organism*** world);

    void print_position() const {
        cout << '(' << position.h << ',' << position.w << ")\n"; }

    virtual void move(Organism*** world) {};

private:
    char type;
    Position position;
    bool moved;
    int breed_interval;
};

vector<Position> Organism::get_target_positions(Organism*** world, int height, int width, char target) const {
    int candidates[] = { -1, 1 }, h, w;
    vector<Position> positions;
    for (int dh : candidates) {
        h = position.h + dh;
        w = position.w;
        if ((0<=h && h<height) && (world[h][w]->get_type() == target)) {
            positions.push_back(Position(h, w));
        }
    }
    for (int dw : candidates) {
        h = position.h;
        w = position.w + dw;
        if ((0<=w && w<width) && (world[h][w]->get_type() == target)) {
            positions.push_back(Position(h, w));
        }
    }
    return positions;
}

Position Organism::get_random_position(Organism*** world) {
    Position ori_pos = get_position();
    Position new_pos;

    int direction = rand() % 4;
    int new_h = ori_pos.h, new_w = ori_pos.w;
    switch (direction) {
        case 0: // up
            if ((new_h-1 >= 0) && (world[new_h-1][new_w]->get_type() == EMPTY)) {
                new_h -= 1;
            }
            break;
        case 1: // down
            if ((new_h+1 <= WORLD_HEIGHT-1) && (world[new_h+1][new_w]->get_type() == EMPTY)) {
                new_h += 1;
            }
            break;
        case 2: // left
            if ((new_w-1 >= 0) && (world[new_h][new_w-1]->get_type() == EMPTY)) {
                new_w -= 1;
            }
            break;
        case 3: // right
            if ((new_w+1 <= WORLD_WIDTH-1) && (world[new_h][new_w+1]->get_type() == EMPTY)) {
                new_w += 1;
            }
            break;
    }

    if ((new_h != ori_pos.h) || (new_w != ori_pos.w)) {
        new_pos = Position(new_h, new_w);
    }

    return new_pos;
}


class Ant : public Organism
{
public:
    Ant(int x, int y) : Organism(ANT, ANT_BREED_INTERVAL, x, y) {}

    virtual void move(Organism*** world);
};

void Ant::move(Organism*** world) {
    Position ori_pos = get_position();
    Position new_pos = get_random_position(world);
    
    if (new_pos.h != -1) {
        set_position(new_pos);
        delete world[new_pos.h][new_pos.w];
        world[new_pos.h][new_pos.w] = this;
        world[ori_pos.h][ori_pos.w] = new Organism;
    }
    set_moved(true);
    // breed
    // vector<Position> positions;
}


class Doodlebug : public Organism
{
public:
    Doodlebug(int x, int y) 
    : Organism(DOODLEBUG, BUG_BREED_INTERVAL, x, y), starve_steps(BUG_STARVE) {}

    int get_starve_steps() const { return starve_steps; }

    virtual void move(Organism*** world);

private:
    int starve_steps;
};

void Doodlebug::move(Organism*** world) {
    Position ori_pos = get_position();

    Position new_pos;
    vector<Position> ant_positions = get_target_positions(world, WORLD_HEIGHT, WORLD_WIDTH, ANT);
    int ant_num = ant_positions.size();
    if (ant_num != 0) { // eat
        new_pos = ant_positions[rand() % ant_num];
    } else { // move
        new_pos = get_random_position(world);
    }

    if (new_pos.h != -1) {
        set_position(new_pos);
        delete world[new_pos.h][new_pos.w];
        world[new_pos.h][new_pos.w] = this;
        world[ori_pos.h][ori_pos.w] = new Organism;
    }
    set_moved(true);
    // breed
    // vector<Position> positions;
}




class Grid
{
public:
    Grid() { Grid(20, 20); }
    Grid(int H, int W);

    void initialize(int num_ants, int num_bugs);

    Organism* get_grid(int h, int w) const { return world[h][w]; }
    Organism*** get_world() const { return world; }

    void update_world(Organism*** new_world) { world = new_world; }
    void critters_step(char type);
    void step_forward();

    void reset_moved();
    
    friend ostream &operator<<(ostream &outs, const Grid g);
    void print_prompt() const { cout << "Press ENTER to continue\n"; };

private:
    int height, width;
    int step;
    Organism*** world;
    bool verbose;
};

ostream &operator<<(ostream &outs, const Grid g) { 
    outs << "\nWorld at time step " << g.step << ":\n\n";
    for (int h = 0; h < WORLD_HEIGHT; h++) {
        for (int w=0; w < WORLD_WIDTH; w++) {
            outs << *(g.get_grid(h, w)) << ' ';
        }
        outs << '\n';
    }
    return outs; 
}

Grid::Grid(int H, int W) : height(H), width(W), step(0) {
    world = new Organism**[H];
    for (int h = 0; h < height; h++) {
        world[h] = new Organism*[W];
    }
}

void Grid::initialize(int num_ants, int num_bugs) {
    int grid_nums = WORLD_HEIGHT * WORLD_WIDTH;
    if (grid_nums < num_ants + num_bugs) {
        cout << "Too many critters to initialize!\n";
        exit(1);
    }
    bool used[grid_nums] = { false };
    
    srand(time(0));
    int number, h, w;
    // init ants
    for (int i = 0; i < num_ants; i++) {
        do {
            number = rand() % grid_nums;
        } while (used[number]);
        used[number] = true;
        h = number / WORLD_HEIGHT;
        w = number % WORLD_WIDTH;

        world[h][w] = new Ant(h, w);
    }

    // init bugs
    for (int i = 0; i < num_bugs; i++) {
        do {
            number = rand() % grid_nums;
        } while (used[number]);
        used[number] = true;
        h = number / WORLD_HEIGHT;
        w = number % WORLD_WIDTH;
        world[h][w] = new Doodlebug(h, w);
    }

    // init the rest positions
    for (int i = 0; i < grid_nums; i++) {
        if (!used[i]) {
            h = i / WORLD_HEIGHT;
            w = i % WORLD_WIDTH;
            world[h][w] = new Organism;
        }
    }

    cout << *this << '\n';
    print_prompt();
}

void Grid::critters_step(char type) {
    Organism* critter;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            critter = world[h][w];
            if ((critter->get_type() == type) && (critter->has_moved() == false)) {
                critter->move(world);

                // cout << *this << '\n';
            }
        }
    }
}

void Grid::step_forward() {
    step++;
    critters_step(DOODLEBUG); 
    cout << "After bugs move" << *this << '\n';
    critters_step(ANT); 
    cout << "After ants move" << *this << '\n';
    reset_moved();
    print_prompt(); 
}

void Grid::reset_moved() {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            world[h][w]->set_moved(false);
        }
    }
}


int main() {
    Grid grid(WORLD_HEIGHT, WORLD_WIDTH);
    int num_ants = 3, num_bugs = 3;
    grid.initialize(num_ants, num_bugs);

    char key;
    while ((key = cin.get()) && (key != 'q')) {
        grid.step_forward();
    }

    return 0;
}

