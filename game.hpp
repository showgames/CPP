enum OBJECT {
    WALL,
    PLAYER,
    ON_GOAL_PLAYER,
    GOAL,
    BAGGAGE,
    ON_GOAL_BAGGAGE,
    EMPTY
};

class STAGE {
    public:
    void init(int height, int width, char* boardData);
    void draw();
    void update(int dir);
    int checkClear();

    private:
    void setDirection();
    void searchPlayer();
    int checkMove(int tmpNext, int tmpNext2);

    int boardHeight;
    int boardWidth;
    OBJECT* board;
    int playerX;
    int playerY;
    int Direction[4];
};