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
    const int sizeOfNebulae{5}; // size of the nebulae array
    AnimationData nebulae[sizeOfNebulae]{}; // array to store the nebulae

    // initializing the nebulae
    for (int i = 0; i < sizeOfNebulae; i++)
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

    // sets the fps
    SetTargetFPS(120);

    // running the game
    while (!WindowShouldClose()) 
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // gets the delta time
        float dT{GetFrameTime()};

        // stores the running time since the last reset
        ryanAnimation.runningTime += GetFrameTime();

        // counts the running time size the last frame update for nebulae
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].runningTime += GetFrameTime();
        }

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

        // updates the nebulae postion with delta time, not frame refresh
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebulaVelocity * dT;
        }

        // updates the picture location on the sprite image
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
        }

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

        // nebulae moving
        for (int i = 0; i < sizeOfNebulae; i++)
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

        // draw ryan
        DrawTextureRec(ryan, ryanAnimation.rec, ryanAnimation.pos, WHITE);

        // draw all the nebulae
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // end drawing
        EndDrawing();
    }

    // cleanup
    UnloadTexture(ryan);
    UnloadTexture(nebula);
    CloseWindow();

    // return
    return 0;
}
