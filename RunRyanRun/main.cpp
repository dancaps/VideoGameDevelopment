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
    int windowDimensions[2]{1500, 800};

    // window configuration
    InitWindow(windowDimensions[0], windowDimensions[1], gameTitle);

    // nebula setup
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // AnimationData nebulaAnimation = {
    //     {0.0, 0.0, static_cast<float>(nebula.width / 8.0), static_cast<float>(nebula.height / 8.0)}, // Rectangle Data
    //     {static_cast<float>(windowDimensions[0]), windowDimensions[1] - static_cast<float>(nebula.height / 8.0)}, // Vector2 data
    //     0, // frame initialization
    //     1.0 / 12.0, // updateTime
    //     0.0, // runningTime
    // };
    // AnimationData nebula2Animation = {
    //     {0.0, 0.0, static_cast<float>(nebula.width / 8.0), static_cast<float>(nebula.height / 8.0)}, // Rectangle Data
    //     {static_cast<float>(windowDimensions[0]) + windowDimensions[0] / 2, windowDimensions[1] - static_cast<float>(nebula.height / 8.0)}, // Vector2 data
    //     0, // frame initialization
    //     1.0 / 18.0, // updateTime
    //     0.0, // runningTime
    // };

    AnimationData nebulae[5]{};

    for (int i = 0; i < 5; i++)
    {
        nebulae[i] = {
            {0.0, 0.0, static_cast<float>(nebula.width / 8.0), static_cast<float>(nebula.height / 8.0)}, // Rectangle Data
            {static_cast<float>(windowDimensions[0]) + (windowDimensions[0] / 2) * i, windowDimensions[1] - static_cast<float>(nebula.height / 8.0)}, // Vector2 data
            0, // frame initialization
            1.0 / 18.0, // updateTime
            0.0, // runningTime
    };
    }
    

    // ryan setup
    Texture2D ryan = LoadTexture("textures/ryan.png");
    AnimationData ryanAnimation = {
        {0.0, 0.0, static_cast<float>(ryan.width / 6.0), static_cast<float>(ryan.height)},
        {static_cast<float>(windowDimensions[0]) / 3, windowDimensions[1] - static_cast<float>(ryan.height)}, 
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

        for (int i = 0; i < 5; i++)
        {
            nebulae[i].runningTime += GetFrameTime();
        }
        
        // nebulae[0].runningTime += GetFrameTime();
        // nebulae[1].runningTime += GetFrameTime();

        // ground check
        if (ryanAnimation.pos.y < windowDimensions[1] - ryanAnimation.rec.height)
        {
            // player in the air
            velocity += gravity * dT; // increases gravity using delta time
            isInAir = true; // updates the flag to show in the air
        }
        else
        {
            // player on the ground
            velocity = 0; // stops falling
            ryanAnimation.pos.y = windowDimensions[1] - ryanAnimation.rec.height; // resets the postion to the ground
            isInAir = false; // updates flag showing not in the air
        }

        // jump when not already in the air
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity; // applies the jumpVelocity to velocity to make the jump
        }

        // animation postion
        ryanAnimation.pos.y += velocity * dT;

        for (int i = 0; i < 5; i++)
        {
            nebulae[i].pos.x += nebulaVelocity * dT;
        }
        
        // nebulae[0].pos.x += nebulaVelocity * dT;
        // nebulae[1].pos.x += nebulaVelocity * dT;

        // update animation frame

        for (int i = 0; i < 5; i++)
        {
            nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
        }
        
        // nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
        // nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;

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

        for (int i = 0; i < 5; i++)
        {
            // many nebula
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                // time to update the nebula frame
                nebulae[i].frame++;

                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }

                nebulae[i].runningTime = 0.0;
            }
        }
        
        // // first nebula
        // if (nebulae[0].runningTime >= nebulae[0].updateTime)
        // {
        //     // time to update the nebula frame
        //     nebulae[0].frame++;

        //     if (nebulae[0].frame > 7)
        //     {
        //         nebulae[0].frame = 0;
        //     }

        //     nebulae[0].runningTime = 0.0;
        // }

        // // second nebula
        // if (nebulae[1].runningTime >= nebulae[1].updateTime)
        // {
        //     // time to update the nebula frame
        //     nebulae[1].frame++;

        //     if (nebulae[1].frame > 7)
        //     {
        //         nebulae[1].frame = 0;
        //     }

        //     nebulae[1].runningTime = 0.0;
        // }

        // draw animations
        DrawTextureRec(ryan, ryanAnimation.rec, ryanAnimation.pos, WHITE);

        for (int i = 0; i < 5; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }
        
        // DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        // DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

        // end drawing
        EndDrawing();
    }

    UnloadTexture(ryan);
    UnloadTexture(nebula);
    CloseWindow();

    // return
    return 0;
}
