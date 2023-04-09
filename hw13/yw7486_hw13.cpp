#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int HEIGHT = 5, WIDTH = 5;

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
    : symbol('-'), breed_interval(-1), position(-1, -1) {}
    // Organism(Position pos)
    // : symbol('-'), breed_interval(-1), position(pos) {}
    Organism(char symbol, int breed_interval, int h, int w) 
    : symbol(symbol), breed_interval(breed_interval), position(h, w) {}

    friend ostream &operator<<(ostream &outs, const Organism &o) { 
        outs << o.symbol; return outs; }

    int get_bread_interval() const { return breed_interval; }
    char get_symbol() { return symbol; }
    Position get_position() { return position; }

    void set_position(int h, int w) { position.h = h; position.w = w; }
    void set_position(Position new_pos) { position = new_pos; }

    vector<Position> get_valid_positions(Organism*** world, int height, int width, char target) const;

    void print_position() const {
        cout << '(' << position.h << ',' << position.w << ")\n"; }

    Organism*** move(Organism*** world);
    virtual void say() { cout << "Critter" << endl; }

private:
    char symbol;
    Position position;
    int breed_interval;
};

Organism*** Organism::move(Organism*** world) {
    Position ori_pos = get_position();
    vector<Position> valid_positions;
    if (symbol == 'X') {
        valid_positions = get_valid_positions(world, HEIGHT, WIDTH, 'o');
    }
    if (symbol == 'o' || valid_positions.size() == 0) {
        valid_positions = get_valid_positions(world, HEIGHT, WIDTH, '-');
    }
    Position new_pos = valid_positions[rand() % valid_positions.size()];
    set_position(new_pos);

    delete world[new_pos.h][new_pos.w];
    world[new_pos.h][new_pos.w] = this;
    world[ori_pos.h][ori_pos.w] = new Organism;

    return world;
}

vector<Position> Organism::get_valid_positions(Organism*** world, int height, int width, char target) const {
    int candidates[] = { -1, 1 }, h, w;
    vector<Position> valid_positions;
    for (int dh : candidates) {
        h = position.h + dh;
        w = position.w;
        if ((0<=h && h<height) && (world[h][w]->get_symbol() == target)) {
            valid_positions.push_back(Position(h, w));
        }
    }
    for (int dw : candidates) {
        h = position.h;
        w = position.w + dw;
        if ((0<=w && w<width) && (world[h][w]->get_symbol() == target)) {
            valid_positions.push_back(Position(h, w));
        }
    }

    return valid_positions;
}


class Ant : public Organism
{
public:
    Ant(int x, int y) : Organism('o', 3, x, y) {}

};


class Doodlebug : public Organism
{
public:
    Doodlebug(int x, int y) : Organism('X', 8, x, y), starve_steps(3) {}

    int get_starve_steps() const { return starve_steps; }

private:
    int starve_steps;
};

class Grid
{
public:
    Grid() { Grid(20, 20); }
    Grid(int H, int W);

    void initialize(int num_ants, int num_bugs);

    Organism* get_pos(int h, int w) const { return world[h][w]; }
    Organism*** get_world() const { return world; }

    void update_world(Organism*** new_world) { world = new_world; }
    void critters_step(char type);
    void step_forward();
    
    friend ostream &operator<<(ostream &outs, const Grid g);
    void print_prompt() const { cout << "Press ENTER to continue\n"; };

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
    int grid_nums = HEIGHT * WIDTH;
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
        h = number / HEIGHT;
        w = number % WIDTH;

        world[h][w] = new Ant(h, w);
    }

    // init bugs
    for (int i = 0; i < num_bugs; i++) {
        do {
            number = rand() % grid_nums;
        } while (used[number]);
        used[number] = true;
        h = number / HEIGHT;
        w = number % WIDTH;
        world[h][w] = new Doodlebug(h, w);
    }

    // init the rest positions
    for (int i = 0; i < grid_nums; i++) {
        if (!used[i]) {
            h = i / HEIGHT;
            w = i % WIDTH;
            world[h][w] = new Organism;
        }
    }

    cout << *this << '\n';
    print_prompt();
}

ostream &operator<<(ostream &outs, const Grid g) { 
    outs << "\nWorld at time step " << g.step << ":\n\n";
    for (int h = 0; h < HEIGHT; h++) {
        for (int w=0; w < WIDTH; w++) {
            outs << *(g.get_pos(h, w)) << ' ';
        }
        outs << '\n';
    }
    
    return outs; 
}

void Grid::critters_step(char type) {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            if (world[h][w]->get_symbol() == type) {
                Organism* critter = world[h][w];
                Organism*** new_world = critter->move(world);
                update_world(new_world);

                // cout << *this << '\n';
            }
        }
    }
}

void Grid::step_forward() {
    step++;
    critters_step('X'); 
    cout << "After bugs move" << *this << '\n';
    critters_step('o'); 
    cout << "After ants move" << *this << '\n';
    print_prompt(); 
}


int main() {
    Grid grid(HEIGHT, WIDTH);
    grid.initialize(3, 3);

    char key;
    while ((key = cin.get()) && (key != 'q')) {
        grid.step_forward();
    }

    return 0;
}

