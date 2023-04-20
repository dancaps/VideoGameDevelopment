#include "raylib.h"

int main() {

    // Window dimensions
    int width{1050};
    int height{600};

    // Circle coordinates
    int circleX{width / 4};
    int circleY{height / 2};
    int circleRadius{50};

    //Circle edges
    int lCircleX{circleX - circleRadius};
    int rCircleX{circleX + circleRadius};
    int tCircleY{circleY - circleRadius};
    int bCircleY{circleY + circleRadius};

    // Axe coordinates
    int axeWidth{50};
    int axeHeight{50};
    int axeX{(width / 2) - (axeWidth / 2)};
    int axeY{0};
    int axeDirection{20};

    // Axe edges
    int lAxeX{axeX};
    int rAxeX{axeX + axeWidth};
    int tAxeY{axeY};
    int bAxeY{axeY + axeHeight};

    bool isCollision = (bAxeY >= tCircleY) && 
                       (tAxeY <= bCircleY) && 
                       (lAxeX <= rCircleX) &&
                       (rAxeX >= lCircleX);

    InitWindow(width, height, "Game");
    SetTargetFPS(60);

    while(WindowShouldClose() == false) {
        // Drawing the window
        BeginDrawing();
        ClearBackground(WHITE);

        if (isCollision) {
            DrawText("Game Over!", (width / 2 - 250), (height / 2 - 40), 100, RED);
        } else {

            // Updating the edges
            lCircleX = circleX - circleRadius;
            rCircleX = circleX + circleRadius;
            tCircleY = circleY - circleRadius;
            bCircleY = circleY + circleRadius;
            lAxeX = axeX;
            rAxeX = axeX + axeWidth;
            tAxeY = axeY;
            bAxeY = axeY + axeHeight;

            // Updating collision
            isCollision = (bAxeY >= tCircleY) && 
                          (tAxeY <= bCircleY) && 
                          (lAxeX <= rCircleX) &&
                          (rAxeX >= lCircleX);

            // Drawing the actors
            DrawCircle(circleX, circleY, circleRadius, BLUE);
            DrawRectangle(axeX, axeY, axeWidth, axeHeight, RED);

            // Moving the axe
            axeY += axeDirection;
            if ((axeY + axeHeight) > height || axeY < 0)
            {
                axeDirection = -axeDirection;
            }

            // Moving the circle within the bounds of the window
            if(IsKeyDown(KEY_D) && circleX < width) {
                circleX += 10;
            }
            if (IsKeyDown(KEY_A) && circleX > 0) {
                circleX -= 10;
            }
            if (IsKeyDown(KEY_W) && circleY > 0) {
                circleY -= 10;
            }
            if (IsKeyDown(KEY_S) && circleY < height) {
                circleY += 10;
            }
        }

        // Ending the drawing
        EndDrawing();
    }
}
