#include <iostream>
#include <vector>

using namespace std;

const int HEIGHT = 20, WIDTH = 20;

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

    friend ostream &operator<<(ostream &outs, const Organism &o) { outs << o.symbol; return outs; }

    int get_bread_interval() const { return breed_interval; }
    char get_symbol() { return symbol; }
    Position get_position() { return position; }

    void set_position(int h, int w) { position.h = h; position.w = w; }
    void set_position(Position new_pos) { position = new_pos; }

    void print_position() const { cout << '(' << position.h << ',' << position.w << ')' << endl; }

    virtual void move(Organism*** &world) {}
    virtual void say() { cout << "Critter" << endl; }

private:
    char symbol;
    Position position;
    int breed_interval;
};

vector<Position> get_valid_positions(Position pos, Organism*** world, int height, int width){
    int candidates[] = { -1, 1 }, h, w;
    vector<Position> valid_positions;
    for (int dh : candidates) {
        h = pos.h + dh;
        w = pos.w;
        if ((0<=h && h<height) && (world[h][w]->get_symbol() == '-')) {
            valid_positions.push_back(Position(h, w));
        }
    }
    for (int dw : candidates) {
        h = pos.h;
        w = pos.w + dw;
        if ((0<=w && w<width) && (world[h][w]->get_symbol() == '-')) {
            valid_positions.push_back(Position(h, w));
        }
    }

    return valid_positions;
}


class Ant : public Organism
{
public:
    Ant(int x, int y) : Organism('o', 3, x, y) {}

    virtual void move(Organism*** &world);
    virtual void say() { cout << "Ant" << endl; }


};

void Ant::move(Organism*** &world) {
    Position ori_pos = get_position();
    vector<Position> valid_positions = get_valid_positions(ori_pos, world, HEIGHT, WIDTH);
    if (valid_positions.size() > 0) {
        Position new_pos = valid_positions[rand() % valid_positions.size()];
        set_position(new_pos);

        world[new_pos.h][new_pos.w] = this;
        world[ori_pos.h][ori_pos.w] = new Organism;
    }
}


class Doodlebug : public Organism
{
public:
    Doodlebug(int x, int y) : Organism('X', 8, x, y), starve_steps(3) {}

    int get_starve_steps() const { return starve_steps; }

    virtual void move(Organism*** &world);
    virtual void say() { cout << "Bug" << endl; }

private:
    int starve_steps;
};

void Doodlebug::move(Organism*** &world) {}


class Grid
{
public:
    Grid() { Grid(20, 20); }
    Grid(int H, int W);

    void initialize(int num_ants, int num_bugs);
    Organism get_pos(int h, int w) const { return world[h][w]; }
    Organism** get_the_world() const { return world; }
    void set_grid(int h, int w, string type);

    // void step_forward();
    // void ants_step();
    // void bugs_step();

    void update_world(Organism** new_world) { world = new_world; }
    void print_world() const;

private:
    int height, width;
    Organism** world;
};

Grid::Grid(int H, int W) : height(H), width(W) {
    world = new Organism*[H];
    for (int h = 0; h < height; h++) {
        world[h] = new Organism[W];
    }
}

void initialize(Organism*** &world, int num_ants, int num_bugs, bool verbose) {
    int grid_nums = HEIGHT * WIDTH;
    bool used[grid_nums] = { false };
        
    int number, h, w;
    for (int i = 0; i < num_ants; i++) {
        do {
            number = rand() % grid_nums;
        } while (used[number]);
        used[number] = true;
        h = number / HEIGHT;
        w = number % WIDTH;

        Ant* ant = new Ant(h, w);
        world[h][w] = ant;
        if (verbose) world[h][w]->say();
    }

    for (int i = 0; i < num_bugs; i++) {
        do {
            number = rand() % grid_nums;
        } while (used[number]);
        used[number] = true;
        h = number / HEIGHT;
        w = number % WIDTH;
        Doodlebug* bug = new Doodlebug(h, w);
        world[h][w] = bug;
        if (verbose) world[h][w]->say();
    }

    for (int i = 0; i < grid_nums; i++) {
        if (!used[i]) {
            h = i / HEIGHT;
            w = i % WIDTH;
            Organism* org = new Organism;
            world[h][w] = org;
        }
    }
}

void print_world(Organism*** world) {
    for (int h = 0; h < HEIGHT; h++) {
        for (int w=0; w < WIDTH; w++) {
            Organism* org = world[h][w];
            cout << org->get_symbol() << ' ';
        }
        cout << endl;
    }
}


int main() {
    // Grid grid(HEIGHT, WIDTH);
    // grid.initialize(100, 5);
    // grid.print_world();

    // Organism** the_world = grid.get_the_world();

    // Ant ant(0, 0);
    // (&ant)->say();
    // ant.say();
    // Organism* org = &ant;
    // org->say();
    // (*org).say();


    // Organism* ant1 = &Ant(0, 0);
    // ant1->say();


    Organism*** the_world = new Organism**[HEIGHT];
    for (int h = 0; h < HEIGHT; h++) {
        the_world[h] = new Organism*[WIDTH];
    };
    initialize(the_world, 100, 5, false);
    print_world(the_world);

    int x, y;
    cin >> x >> y;
    Organism* ant = the_world[x][y];
    ant->move(the_world);

    // ant.move(the_world);
    
    print_world(the_world);
    

    return 0;
}