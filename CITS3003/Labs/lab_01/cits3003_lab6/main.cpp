#include <iostream>

// A useful shorthand that not all compilers provide by default
using uint = unsigned int;

#ifdef _MSC_VER
// This is needed to be able to use M_PI on MSVC compiler
#define _USE_MATH_DEFINES
#include <math.h>
#endif

// Include the math library we will be using, GLM
#include <glm/glm.hpp>
// Also include some helpers for common transformation matrices
#include <glm/gtx/transform.hpp>

// Include the glad lib, which contains our OpenGL bindings
#include <glad/gl.h>

// Include the GLFW lib, which is out windowing library, but also tell it
// to not include its own OpenGL bindings with the use of the GLFW_INCLUDE_NONE macro.
// This is done to prevent conflicts
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
// Define the OpenGL version to use at runtime, later passed to GLFW since it
// is responsible for creating the context.
// 4.1 is the highest version supported by basically all Windows, Linux and Mac machines.
// This is limited by Apple who have deprecated support for OpenGL and so are no longer
// supporting newer version (currently there is up to 4.6).
#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 1

// Include some code that helps with shader creation
#include "helpers/ShaderHelper.h"

// Include some code that helps with using ImGui
#include "helpers/imgui/ImGuiManager.h"

#include <deque>

// Some constant window properties we define here for now, since we currently don't handle
// window resizing.
// #define WINDOW_WIDTH 512
// #define WINDOW_HEIGHT 512
#define WINDOW_TITLE "Lab 6"

// A flag to enable or disable vsync (aka frame limiting)
#define V_SYNC false


int window_width = 512;
int window_height = 512;


 std::deque<float> frame_times{};

const int NUM_SIDES = 6;
const int NUM_TRIANGLES = 2 * NUM_SIDES;
const int NUM_ELEMENTS = 3 * NUM_TRIANGLES;
const int NUM_VERTICES = 8;

// This time create a struct representing the data of a single vertex, because we will be
// interleaving the vertex attributes instead of laying it out with each attribute
// together like before.
struct Vertex {
    glm::vec3 position;
    glm::vec3 colour;
};


Vertex vertices[NUM_VERTICES] = {
        Vertex { glm::vec3{ -0.5, -0.5, -0.5 }, glm::vec3{0.0, 0.0, 0.0} },
        Vertex { glm::vec3{ -0.5, -0.5,  0.5 }, glm::vec3{0.0, 0.0, 1.0} },
        Vertex { glm::vec3{ -0.5,  0.5, -0.5 }, glm::vec3{0.0, 1.0, 0.0} },
        Vertex { glm::vec3{ -0.5,  0.5,  0.5 }, glm::vec3{0.0, 1.0, 1.0} },

        Vertex { glm::vec3{  0.5, -0.5, -0.5 }, glm::vec3{1.0, 0.0, 0.0} },
        Vertex { glm::vec3{  0.5, -0.5,  0.5 }, glm::vec3{1.0, 0.0, 1.0} },
        Vertex { glm::vec3{  0.5,  0.5, -0.5 }, glm::vec3{1.0, 1.0, 0.0} },
        Vertex { glm::vec3{  0.5,  0.5,  0.5 }, glm::vec3{1.0, 1.0, 1.0} }
};

// The following builds triangles from the 8 vertices above,
// using numbers 0-7 to refer to the element positions in the array
uint elements[NUM_ELEMENTS] = {
        1, 5, 3,
        7, 3, 5,

        0, 4, 2,
        6, 2, 4,

        4, 6, 5,
        7, 5, 6,

        0, 2, 1,
        3, 1, 2,

        2, 3, 6,
        7, 6, 3,

        0, 1, 4,
        5, 4, 1
};

int xyzw_multipliers_location;

void init() {
    // Create a vertex array object
    uint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and initialize a buffer object for vertex data
    uint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    // Since the data is laid out contiguously already,
    // can just directly upload instead of needing to do it in two steps
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * NUM_VERTICES, vertices, GL_STATIC_DRAW);

    // Load shaders and use the resulting shader program
    uint program = ShaderHelper::load_shader("vert.glsl", "frag.glsl");
    glUseProgram(program);

    // Initialize the vertex position attribute from the vertex shader.
    // Note: that this time in the shader we use a layout qualifier to specify the attribute location,
    // so there is no need to fetch it.
    glEnableVertexAttribArray(0);
    // Also note: now that we are interleaving data, the stride and offset are different
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));

    // Likewise, initialize the vertex color attribute. And likewise location is specified in the shader.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, colour));

    // ADDED: load the element index data
    uint element_buffer;
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * NUM_ELEMENTS, elements, GL_STATIC_DRAW);

    xyzw_multipliers_location = glGetUniformLocation(program, "xyzwMultipliers");

    // We need to enable the depth test to discard fragments that are behind
    // previously drawn fragments for the same pixel.
    glEnable(GL_DEPTH_TEST);

    glClearColor(1.0, 1.0, 1.0, 1.0); /* white background */
}

bool animate_rotation = true;
glm::vec3 rotation_angles{0.0f};
glm::vec3 rotation_speed{1.0f};

glm::vec3 scale_factors{0.250f, 1.0f, 1.0f};

glm::vec3 translation{1.0f, 1.0f, 1.0f};

float fov = 80.0f;

// Perspective projection
glm::mat4 projection = glm::perspective(glm::radians(fov), 1.0f, 0.1f, 10.0f);

// Move the scene backwards relative to the camera
glm::mat4 view = glm::translate(glm::vec3{0.0f, 0.0f, -1.5f});



void ui() {
    // Create an ImGUI window, the function returns true if the window is expanded and false if collapsed,
    // so we use an if to only add things to the window it is open
    if (ImGui::Begin("ImGUI Window", nullptr, ImGuiWindowFlags_NoFocusOnAppearing)) {
        // Add a checkbox to control whether to animate the rotation
        ImGui::Checkbox("Animate Rotation", &animate_rotation);

        // Add a drag to edit the 3 components of the rotation_speed vector, setting the drag speed
        // to 0.1f and don't clamp the range.
        ImGui::DragFloat3("Rotation Speeds", &rotation_speed[0], 0.1f);

        // Add a slider to edit the 3 components of the rotation_angle vector, setting the rang to be [0, 2pi]
        ImGui::SliderFloat3("Rotation Angle", &rotation_angles[0], 0.0f, 2.0f * (float) M_PI);

        // Add a slider to edit the 3 components of the scale_factors vector, setting the range to be [0.1, 2.0]
        ImGui::DragFloat3("Scale Factors", &scale_factors[0], 0.1f);

        // Add a slider to edit the 3 components of the translation vector, setting the range to be [-1.0, 1.0]
        ImGui::DragFloat3("Translation", &translation[0], 0.1f);

        //Adding a slider to edit POV using boolean of perspective
        if (ImGui::SliderFloat("Camera FOV", &fov, 0.0f, 180.0f)) {
            projection = glm::perspective(glm::radians(fov), (float) window_width / (float) window_height, 0.1f, 10.0f);
        }


    }
    // Since ImGUI is an immediate mode UI with hidden internal state, we need to explicitly tell it that
    // we are done talking about the current window, to do that we call End();
    ImGui::End();
}


//Did not implement "If the left mouse is down and ImGUI isn't capturing it, 
// use the mouse position from previous calls to the callback to calculate a change in mouse position (a delta). 
// Then this can be used to update the x and y components of a global camera_position variable, and then used to recalculate the view matrix. "
void mousemove_callback(GLFWwindow *window, double xpos, double ypos) {

    int pressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    if (pressed == GLFW_PRESS && !ImGuiManager::want_capture_mouse()) {
        float x = (float)xpos / (float)window_width - 0.5;
        float y = 0.5 - (float)ypos / (float)window_height;

        

        view = glm::translate(glm::vec3(x, y, -1.5f));
    }
}


void framebuffersizeCallback(GLFWwindow *window, int width, int height) {
    window_width = width;
    window_height = height;
    glViewport(0, 0, width, height);
    projection = glm::perspective(glm::radians(80.0f), (float) width / (float) height, 0.1f, 10.0f);
    
}

void draw_cube(glm::mat4 model) {

    glm::mat4 projection_view_model = projection * view *model;

    glUniformMatrix4fv( xyzw_multipliers_location, 1, GL_FALSE, &projection_view_model[0][0] );
    glDrawElements( GL_TRIANGLES, NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr);}

void draw(GLFWwindow *window, ImGuiManager& imgui_manager) {
    // Tell ImGUI we are starting a new frame
    imgui_manager.new_frame();
    ImGuiManager::enable_main_window_docking();

    // Here we add the UI elements, this can be called any time between imgui_manager.new_frame() and imgui_manager.render().
    // However, values update by the UI are updated when calling the function like DragFloat3, that means that processing the UI
    // before using the values like this will minimise the latency between changing something, and it's showing up. As otherwise
    // it wouldn't have a visual effect until the next frame.
    ui();

    static auto last_time = glfwGetTime();
    auto time = glfwGetTime();
    auto delta = (float) (time - last_time);
    last_time = time;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (animate_rotation) {
        rotation_angles += delta * rotation_speed;
        rotation_angles = glm::mod(rotation_angles, 2.0f * (float) M_PI);
    }

    // Note that the glm matrix constructor takes column vectors,
    // so it visually appears to be the transpose of the actual matrix.
    auto x_angle = rotation_angles.x;

    glm::mat4 x_rotation = glm::rotate(rotation_angles.x, glm::vec3{1.0f, 0.0f,0.0f});

        auto y_angle = rotation_angles.y;

    glm::mat4 y_rotation = glm::rotate(rotation_angles.y, glm::vec3{0.0f, 1.0f, 0.0f});

        auto z_angle = rotation_angles.z;

    glm::mat4 z_rotation = glm::rotate(rotation_angles.z, glm::vec3{0.0f, 0.0f, 1.0f});

    glm::mat4 scale_matrix = glm::scale(scale_factors);
    glm::mat4 translation_matrix = glm::translate(translation);
    

    // Since we want the shrink to handle in model space we put in on the right,
    // because matrices are "applied" right to left in the conventions most commonly used with OpenGL
    glm::mat4 combined_matrix_A =  translate(glm::vec3{-0.5, 0.5, 0}) * glm::scale(glm::vec3{0.3}) * z_rotation * y_rotation * x_rotation * scale_matrix;
    draw_cube(combined_matrix_A);

    glm::mat4 combined_matrix_B =  translate(glm::vec3{0.5, 0.5, 0}) *glm::scale(glm::vec3{0.3}) * z_rotation * y_rotation * x_rotation * scale_matrix ;
    draw_cube(combined_matrix_B);

    combined_matrix_B =  translate(glm::vec3{0.5, 0.5, 0}) * glm::scale(glm::vec3{0.3}) * z_rotation * y_rotation * x_rotation *scale_matrix * translation_matrix ;
    draw_cube(combined_matrix_B);

    glm::mat4 combined_matrix_C =   translate(glm::vec3{-0.5, -0.5, 0}) * glm::scale(glm::vec3{0.3}) * z_rotation * y_rotation * x_rotation * scale_matrix;
    draw_cube(combined_matrix_C);

    combined_matrix_C =   translate(glm::vec3{-0.5, -0.5, 0})* glm::scale(glm::vec3{0.3}) * z_rotation * y_rotation * x_rotation * translation_matrix *scale_matrix;
    draw_cube(combined_matrix_C);

    glm::mat4 combined_matrix_D =   translate(glm::vec3{0.5, -0.5, 0})  * glm::scale(glm::vec3{0.3}) * z_rotation * y_rotation * x_rotation * scale_matrix;
    draw_cube(combined_matrix_D);

    combined_matrix_D =   translate(glm::vec3{0.5, -0.5, 0}) * glm::scale(glm::vec3{0.3}) * translation_matrix * z_rotation * y_rotation * x_rotation   * scale_matrix;
    draw_cube(combined_matrix_D);

    

    // Tell ImGUI to now render itself, this is done after drawing the scene so that it appears on top.
    imgui_manager.render();

    glfwSwapBuffers(window);

    frame_times.push_back(delta);
    while (frame_times.size() > 100) {
	frame_times.pop_front();}

    float sum = 0.0f;
    for (const auto &dt: frame_times) {
            sum += dt;
        }
    float average_dt = sum / (float) frame_times.size();
    float average_fps = 1.0f / average_dt;

    std::string title = "Lab 6: FPS: " + std::to_string(average_fps);
    glfwSetWindowTitle(window, title.c_str());
}

void key_callback(GLFWwindow *window, int key, int /*scancode*/, int /*action*/, int /*mods*/) {
    switch (key) {
        case GLFW_KEY_ESCAPE: {
            // Don't directly close this time, instead tell GLFW to mark the window as "Should close",
            // the same as if we have hit the close button.
            glfwSetWindowShouldClose(window, true);
            break;
        }
    }
}

void refresh_callback(GLFWwindow *window) {
    auto* imgui_manager = static_cast<ImGuiManager *>(glfwGetWindowUserPointer(window));
    draw(window, *imgui_manager);
}

// A callback function that we give GLFW to report errors with.
void glfwErrorCallback(int code, const char *msg) {
    std::cout << "GLFW Error (" << code << ")\n\t" << "msg: " << msg << std::endl;
}

int main() {
    glfwSetErrorCallback(glfwErrorCallback);
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(window_width, window_height, WINDOW_TITLE, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    //glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffersizeCallback);

     glfwSetCursorPosCallback(window, mousemove_callback);

    glfwSwapInterval(V_SYNC ? 1 : 0);

    int status = gladLoadGL((GLADloadfunc) glfwGetProcAddress);
    if (!status) {
        std::cerr << "Failed to Load OpenGL functions, via GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Print some info about the OpenGL context
    std::cout << "" << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "" << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "" << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "" << "OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "" << "------------------------------------------------------------" << std::endl;
    std::cout << "" << std::endl;

    // Set most callbacks before creating ImGuiManager, as ImGUI will hook into
    // the same glfw callbacks and chain call the ones previous set.
    // We could do the same if we set out callbacks afterwards, but this is less work.
    glfwSetKeyCallback(window, key_callback);

    ImGuiManager imgui_manager{window};

    // Store a pointer to ImGuiManager with the window, so that we can access it in refresh_callback
    glfwSetWindowUserPointer(window, &imgui_manager);

    init();

    // This callback may only end up being called very rarely if at all, hence why we use a main loop.
    // Also, ImGuiManager doesn't override this callback, so it can be called afterwards.
    // In fact in needs to be set after init() and glfwSetWindowUserPointer() otherwise the draw() call
    // will be invalid.
    glfwSetWindowRefreshCallback(window, refresh_callback);

    // GLFW works a bit differently than GLUT, we have to write the main loop ourselves, though this gives more control.
    // This does have the downside though that the loop may block when resizing or moving the window on some systems,
    // see docs of glfwPollEvents call for more info, this is why we also use glfwSetWindowRefreshCallback.
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // Tell glfw to check for new events that have arrived from the OS since the last call.

        draw(window, imgui_manager); // Just call draw
    }

    ImGuiManager::cleanup();

    glfwDestroyWindow(window);
    glfwTerminate();
}
