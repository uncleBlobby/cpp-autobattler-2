#include "base.h"

#include "game.h"

int main() {
    std::cout << "hello, cpp-autobattler-2" << std::endl;

    rl::InitWindow(0, 0, "cpp-autobattler-2");

    rl::SetTargetFPS(60);
    rl::SetWindowMonitor(0);

    Game g = Game();

    g.InitPlayer();

    while (!rl::WindowShouldClose()) {
        float dt = rl::GetFrameTime();
        rl::BeginDrawing();

        rl::ClearBackground(rl::RAYWHITE);

        g.Update(dt);
        g.Draw();

        rl::EndDrawing();
    }
}