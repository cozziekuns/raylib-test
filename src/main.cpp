#include <cmath>

#include <raylib.h>
#include <raymath.h>

const float SQRT_3 = 1.7320508f;

// TODO: Figure out how this is actually calculated, some world space -> screen space thing
const float CUBE_HEIGHT = 0.81649658092f; // sqrt(2 / 3)

int main() {
  const int screenWidth = 1280;
  const int screenHeight = 720;

  Camera3D camera = { 0 };

  // Camera rotation about the y axis, in radians. Basically when we "rotate" the camera,
  // the camera is actually move about the y-axis in a unit circle while looking at the
  // fixed point (0, 0, 0).
  // To keep the dimetric projection, this needs to end up being locked at pi / 4,
  // and incremented by pi / 2.
  float t = PI / 4.0f;  

  camera.position = (Vector3) { 10.0f, std::sqrt(200.0f) / SQRT_3, 10.0f }; // Camera position
  camera.target = (Vector3) { 0.0f, 0.0f, 0.0f };      // Camera looking at point
  camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 10.0f;                                 // Camera field-of-view Y
  camera.projection = CAMERA_ORTHOGRAPHIC;             // Camera mode type

  Vector3 cubePosition = { 0.5f, CUBE_HEIGHT / 2, 0.5f };

  InitWindow(screenWidth, screenHeight, "Example Game");
  SetTargetFPS(60);

   while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_SPACE)) {
      camera.position.y += 0.5f; 
    }

    if (IsKeyDown(KEY_BACKSPACE)) {
      camera.position.y -= 0.5f;
    }

    if (IsKeyDown(KEY_Z)) {
      t -= PI / 64;

      camera.position.x = std::sqrt(200) * std::cos(t);
      camera.position.z = std::sqrt(200) * std::sin(t);  
    }

    if (IsKeyDown(KEY_X)) {
      t += PI / 64;

      camera.position.x = std::sqrt(200) * std::cos(t);
      camera.position.z = std::sqrt(200) * std::sin(t);  
    }
     
    BeginDrawing();

      ClearBackground(RAYWHITE);      
      DrawFPS(32, 32);

      BeginMode3D(camera);
        DrawCube(cubePosition, 1.0f, CUBE_HEIGHT, 1.0f, RED);
        DrawCubeWires(cubePosition, 1.0f, CUBE_HEIGHT, 1.0f, SKYBLUE);
        DrawGrid(9, 1.0f);
      EndMode3D();
    
      DrawText("Congrats! Your raylib setup is working!", 32, 64, 20, LIGHTGRAY);
      DrawText(TextFormat("Camera.x: %02.02f", camera.position.x), 32, 96,  20, LIGHTGRAY);
      DrawText(TextFormat("Camera.y: %02.02f", camera.position.y), 32, 128, 20, LIGHTGRAY);
      DrawText(TextFormat("Camera.z: %02.02f", camera.position.z), 32, 160, 20, LIGHTGRAY);
      DrawText(TextFormat("Radians: %02.02f", t), 32, 192, 20, LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
