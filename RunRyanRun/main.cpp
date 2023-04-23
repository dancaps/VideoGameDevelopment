#include "raylib.h"

struct AnimationData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // game setup variables
    const char gameTitle[15]{"Run Ryan, Run!"};
    const int gameWidth{1500};
    const int gameHeight{800};

    // window configuration
    InitWindow(gameWidth, gameHeight, gameTitle);

    // nebula setup
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimationData nebulaAnimation = {
        {0.0, 0.0, static_cast<float>(nebula.width / 8.0), static_cast<float>(nebula.height / 8.0)}, // Rectangle Data
        {gameWidth, gameHeight - static_cast<float>(nebula.height / 8.0)}, // Vector2 data
        0, // frame initialization
        1.0 / 12.0, // updateTime
        0.0, // runningTime
    };
    AnimationData nebula2Animation = {
        {0.0, 0.0, static_cast<float>(nebula.width / 8.0), static_cast<float>(nebula.height / 8.0)}, // Rectangle Data
        {gameWidth + gameWidth / 2, gameHeight - static_cast<float>(nebula.height / 8.0)}, // Vector2 data
        0, // frame initialization
        1.0 / 18.0, // updateTime
        0.0, // runningTime
    };

    // ryan setup
    Texture2D ryan = LoadTexture("textures/ryan.png");
    AnimationData ryanAnimation = {
        {0.0, 0.0, static_cast<float>(ryan.width / 6.0), static_cast<float>(ryan.height)},
        {gameWidth / 3, gameHeight - static_cast<float>(ryan.height)}, 
        0,
        1.0 / 12.0,
        0.0
    };

    // game physics
    const int jumpVelocity{-1500}; // pixels/sec
    int velocity{0}; 
    bool isInAir{};
    const int gravity{4000}; // (pixels/sec)/sec
    const int nebulaVelocity{-500};

    SetTargetFPS(120);

    while (!WindowShouldClose()) 
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // gets the delta time
        float dT{GetFrameTime()};

        // stores the running time since the last reset
        ryanAnimation.runningTime += GetFrameTime();
        nebulaAnimation.runningTime += GetFrameTime();
        nebula2Animation.runningTime += GetFrameTime();

        // ground check
        if (ryanAnimation.pos.y < gameHeight - ryanAnimation.rec.height)
        {
            // player in the air
            velocity += gravity * dT; // increases gravity using delta time
            isInAir = true; // updates the flag to show in the air
        }
        else
        {
            // player on the ground
            velocity = 0; // stops falling
            ryanAnimation.pos.y = gameHeight - ryanAnimation.rec.height; // resets the postion to the ground
            isInAir = false; // updates flag showing not in the air
        }

        // jump when not already in the air
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity; // applies the jumpVelocity to velocity to make the jump
        }

        // animation postion
        ryanAnimation.pos.y += velocity * dT;
        nebulaAnimation.pos.x += nebulaVelocity * dT;
        nebula2Animation.pos.x += nebulaVelocity * dT;

        // update animation frame
        nebulaAnimation.rec.x = nebulaAnimation.frame * nebulaAnimation.rec.width;
        nebula2Animation.rec.x = nebula2Animation.frame * nebula2Animation.rec.width;
        //nebulaRec.x = nebulaFrame * nebulaRec.width;

        // ryan moving
        if (ryanAnimation.runningTime >= ryanAnimation.updateTime) 
        {
            // update the player frame
            if (!isInAir)
            {
                ryanAnimation.rec.x = ryanAnimation.frame * ryanAnimation.rec.width;
                ryanAnimation.frame++;
                if (ryanAnimation.frame > 5)
                {
                    ryanAnimation.frame = 0;
                }
            }
            else
            {
                // uses the first image in the sprite as the jump image
                ryanAnimation.rec.x = 0.0;
            }
            ryanAnimation.runningTime = 0.0;
        }

        // first nebula
        if (nebulaAnimation.runningTime >= nebulaAnimation.updateTime)
        {
            // time to update the nebula frame
            nebulaAnimation.frame++;

            if (nebulaAnimation.frame > 7)
            {
                nebulaAnimation.frame = 0;
            }

            nebulaAnimation.runningTime = 0.0;
        }

        // second nebula
        if (nebula2Animation.runningTime >= nebula2Animation.updateTime)
        {
            // time to update the nebula frame
            nebula2Animation.frame++;

            if (nebula2Animation.frame > 7)
            {
                nebula2Animation.frame = 0;
            }

            nebula2Animation.runningTime = 0.0;
        }

        // draw animations
        DrawTextureRec(ryan, ryanAnimation.rec, ryanAnimation.pos, WHITE);
        DrawTextureRec(nebula, nebulaAnimation.rec, nebulaAnimation.pos, WHITE);
        DrawTextureRec(nebula, nebula2Animation.rec, nebula2Animation.pos, RED);

        // end drawing
        EndDrawing();
    }

    UnloadTexture(ryan);
    UnloadTexture(nebula);
    CloseWindow();

    // return
    return 0;
}
