#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int WORLD_HEIGHT = 20, 
          WORLD_WIDTH = 20;
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
    : type(EMPTY), breed_interval(-1), steps_since_breed(-1), position(-1, -1), moved(false) {}
    Organism(char type, int h, int w) 
    : type(type), steps_since_breed(0), position(h, w), moved(false) {
        breed_interval = (type == ANT) ? ANT_BREED_INTERVAL : BUG_BREED_INTERVAL;
    }

    friend ostream &operator<<(ostream &outs, const Organism &o) { 
        outs << o.type; return outs; }

    char get_type() { return type; }
    Position get_position() { return position; }
    bool has_moved() { return moved; }
    int get_breed_steps() const { return steps_since_breed; }

    void set_position(int h, int w) { position.h = h; position.w = w; }
    void set_position(Position new_pos) { position = new_pos; }
    void set_moved(bool status) { moved = status; }
    void reset_breed_steps() { steps_since_breed = 0; }

    vector<Position> get_target_positions(Organism*** world, char target) const;
    Position get_random_position(Organism*** world);

    virtual void move(Organism*** world) {}
    Position breed(Organism*** world);

private:
    char type;
    Position position;
    bool moved;
    int breed_interval;
    int steps_since_breed;
};

vector<Position> Organism::get_target_positions(Organism*** world, char target) const {
    int candidates[] = { -1, 1 }, h, w;
    vector<Position> positions;
    for (int dh : candidates) {
        h = position.h + dh;
        w = position.w;
        if ((0<=h && h<WORLD_HEIGHT) && (world[h][w]->get_type() == target)) {
            positions.push_back(Position(h, w));
        }
    }
    for (int dw : candidates) {
        h = position.h;
        w = position.w + dw;
        if ((0<=w && w<WORLD_WIDTH) && (world[h][w]->get_type() == target)) {
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

Position Organism::breed(Organism*** world) {
    Position breed_pos;
    if (++steps_since_breed == breed_interval) {
        reset_breed_steps();
        vector<Position> empty_positions = get_target_positions(world, EMPTY);
        int empty_num = empty_positions.size();
        if (empty_num != 0) {
            breed_pos = empty_positions[rand() % empty_num];
            delete world[breed_pos.h][breed_pos.w];
        }
    }
    return breed_pos;
}


class Ant : public Organism
{
public:
    Ant(int x, int y) : Organism(ANT, x, y) {}
    Ant(Position pos) : Organism(ANT, pos.h, pos.w) {}

    virtual void move(Organism*** world);
};

void Ant::move(Organism*** world) {
    // moving
    Position ori_pos = get_position();
    Position new_pos = get_random_position(world);
    if (new_pos.h != -1) {
        set_position(new_pos);
        delete world[new_pos.h][new_pos.w];
        world[new_pos.h][new_pos.w] = this;
        world[ori_pos.h][ori_pos.w] = new Organism;
    }
    set_moved(true);

    // breeding
    Position breed_pos = breed(world);
    if (breed_pos.h != -1) {
        world[breed_pos.h][breed_pos.w] = new Ant(breed_pos);
    }
}


class Doodlebug : public Organism
{
public:
    Doodlebug(int x, int y) 
    : Organism(DOODLEBUG, x, y), steps_until_starve(BUG_STARVE) {}
    Doodlebug(Position pos) 
    : Organism(DOODLEBUG, pos.h, pos.w), steps_until_starve(BUG_STARVE) {}

    void reset_starve_steps() { steps_until_starve = BUG_STARVE; }

    virtual void move(Organism*** world);

private:
    int steps_until_starve;
};

void Doodlebug::move(Organism*** world) {
    // eating or moving 
    Position ori_pos = get_position();
    Position new_pos;
    vector<Position> ant_positions = get_target_positions(world, ANT);
    int ant_num = ant_positions.size();
    if (ant_num != 0) { // eat
        reset_starve_steps();
        new_pos = ant_positions[rand() % ant_num];
    } else { // move
        steps_until_starve--;
        new_pos = get_random_position(world);
    }

    if (new_pos.h != -1) {
        set_position(new_pos);
        delete world[new_pos.h][new_pos.w];
        world[new_pos.h][new_pos.w] = this;
        world[ori_pos.h][ori_pos.w] = new Organism;
    }
    set_moved(true);
    
    // breeding
    Position breed_pos = breed(world);
    if (breed_pos.h != -1) {
        world[breed_pos.h][breed_pos.w] = new Doodlebug(breed_pos);
    }

    // starving
    if (steps_until_starve == 0) {
        Position pos = get_position();
        world[pos.h][pos.w] = new Organism;
        delete this;
    }
}


class Grid
{
public:
    Grid() { Grid(20, 20); }
    Grid(int H, int W);

    void initialize(int num_ants, int num_bugs);

    Organism*** get_world() const { return world; }

    void update_world(Organism*** new_world) { world = new_world; }
    void critters_step(char type);
    void step_forward(bool verbose);

    void reset_moved();
    
    void print_prompt() const { cout << "Press ENTER to continue\n"; };
    void print_world() const;
    void print_statistics() const;

private:
    int height, width;
    int step;
    Organism*** world;
    bool verbose;
};

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

    print_world();
}

void Grid::critters_step(char type) {
    Organism* critter;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            critter = world[h][w];
            if ((critter->get_type() == type) && (critter->has_moved() == false)) {
                critter->move(world);
            }
        }
    }
}

void Grid::step_forward(bool verbose) {
    step++;
    critters_step(DOODLEBUG); 
    if (verbose) { 
        cout << "After bugs move";
        print_world();
        print_statistics();
    }
    critters_step(ANT); 
    if (verbose) cout << "After ants move";
    print_world();
    reset_moved();
}

void Grid::reset_moved() {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            world[h][w]->set_moved(false);
        }
    }
}

void Grid::print_world() const {
    cout << "\nWorld at time step " << step << ":\n\n";
    for (int h = 0; h < WORLD_HEIGHT; h++) {
        for (int w=0; w < WORLD_WIDTH; w++) {
            cout << *(world[h][w]) << ' ';
        }
        cout << '\n';
    }
    cout << "\nPress ENTER to continue\n";
}

void Grid::print_statistics() const {
    int ants = 0, bugs = 0;
    char type;
    for (int h = 0; h < WORLD_HEIGHT; h++) {
        for (int w=0; w < WORLD_WIDTH; w++) {
            switch (world[h][w]->get_type()) {
            case ANT:
                ants++; break;
            case DOODLEBUG:
                bugs++; break;
            }
        }
    }
    cout << "Ants: " << ants << "\tBugs: " << bugs << "\n";
}


int main() {
    Grid grid(WORLD_HEIGHT, WORLD_WIDTH);
    int num_ants = 100, num_bugs = 5;
    grid.initialize(num_ants, num_bugs);

    char key;
    while ((key = cin.get()) && (key != 'q')) {
        grid.step_forward(false);
        grid.print_statistics();
    }

    return 0;
}
