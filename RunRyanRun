#include "raylib.h"

int main()
{
    // game setup variables
    const char gameTitle[15]{"Run Ryan, Run!"};
    const int gameWidth{1500};
    const int gameHeight{800};

    // window configuration
    InitWindow(gameWidth, gameHeight, gameTitle);

    // ryan setup
    Texture2D ryan = LoadTexture("textures/ryan.png");
    Rectangle ryanRec;
    ryanRec.width = ryan.width / 6;
    ryanRec.height = ryan.height;
    ryanRec.x = 0;
    ryanRec.y = 0;
    Vector2 ryanPos;
    ryanPos.x = gameWidth / 3;
    ryanPos.y = gameHeight - ryanRec.height;

    // animation frame
    int frame{};
    const float updateTime{1.0 / 12.0};
    float runningTime{};

    // game physics
    const int jumpVelocity{-1500}; // pixels/sec
    int velocity{0}; 
    bool isInAir{};
    const int gravity{4000}; // (pixels/sec)/sec

    SetTargetFPS(120);

    while (!WindowShouldClose()) 
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // gets the delta time
        float dT{GetFrameTime()};

        runningTime += GetFrameTime();

        // ground check
        if (ryanPos.y < gameHeight - ryanRec.height)
        {
            // we are in the air
            velocity += gravity * dT; // increases gravity using delta time
            isInAir = true; // updates the flag to show in the air
        }
        else
        {
            // we are on the ground
            velocity = 0; // stops falling
            ryanPos.y = gameHeight - ryanRec.height; // resets the postion to the ground
            isInAir = false; // updates flag showing not in the air
        }

        // jump when not already in the air
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity; // Applies the jumpVelocity to velocity to make the jump
        }

        ryanPos.y += velocity * dT;

        // Update animation frame
        ryanRec.x = frame * ryanRec.width;

        if (runningTime >= updateTime) 
        {
            //time to update the frame
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
            runningTime = 0.0;
        }

        // draw rectangle
        DrawTextureRec(ryan, ryanRec, ryanPos, WHITE);

        // end drawing
        EndDrawing();
    }

    UnloadTexture(ryan);
    CloseWindow();

    // return
    return 0;
}
