#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <random>

#include "Model.h"
#include "Camera.h"
#include "Animator.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
   // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ClosedGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    const char* founderTitanModelPath = "Resources/models/founder/founder.fbx";
    const char* colossalTitanModelPath = "Resources/models/colossal/colossal.fbx";

    const int NUM_TITANS = 10;
    const int NUM_TITAN_ROWS = 20;
    std::pair<int, int> titanTranslate[NUM_TITAN_ROWS][NUM_TITANS];

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> randTitanXDis(60, 90);
    std::uniform_int_distribution<> randTitanYDis(60, 80);

    Model* colossalTitanModel = new Model(const_cast<char*>(colossalTitanModelPath));
    Animation* rumblingAnimation = new Animation(const_cast<char*>(colossalTitanModelPath), colossalTitanModel);
    Animator* animator = new Animator(rumblingAnimation);

    for (int i = 0; i < NUM_TITAN_ROWS; i++) {
        for (int j = 0; j < NUM_TITANS; j++) {
            titanTranslate[i][j] = { randTitanXDis(gen), randTitanYDis(gen) };
        }
    }

    Model* founderTitanModel = new Model(const_cast<char*>(founderTitanModelPath));

    Shader titanShader("resources/shaders/AnimModel.shader");
    Shader founderShader("resources/shaders/StaticModel.shader");

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = 0.5f * (currentFrame - lastFrame);
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        animator->UpdateAnimation(deltaTime);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(3.0, -1.0, 0.0);
        glVertex3f(-1.0, 3.0, 0.0);
        glEnd();

        titanShader.bind();

        for (int i = 0; i < NUM_TITAN_ROWS; i++) {
            for (int j = 0; j < NUM_TITANS; j++) {
                // pass projection matrix to shader (note that in this case it could change every frame)
                glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
                titanShader.setUniformMat4f("projection", projection);

                // camera/view transformation
                glm::mat4 view = camera.getViewMatrix();
                titanShader.setUniformMat4f("view", view);

                auto transforms = animator->GetFinalBoneMatrices();
                for (int i = 0; i < transforms.size(); ++i)
                    titanShader.setUniformMat4f("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

                glm::mat4 model = glm::mat4(1.0f);

                // it's a bit too big for our scene, so scale it down
                model = glm::scale(model, glm::vec3(.0005f, .0005f, .0005f));
                model = glm::translate(model, glm::vec3(titanTranslate[i][j].first * i, 0.0f, titanTranslate[i][j].second * j));

                //model = glm::rotate(model, (float)glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                titanShader.setUniformMat4f("model", model);

                colossalTitanModel->Draw(titanShader);
            }
        }

        titanShader.unbind();

        founderShader.bind();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        founderShader.setUniformMat4f("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.getViewMatrix();
        founderShader.setUniformMat4f("view", view);

        auto transforms = animator->GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i)
            founderShader.setUniformMat4f("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

        glm::mat4 model = glm::mat4(1.0f);

        // it's a bit too big for our scene, so scale it down
        model = glm::scale(model, glm::vec3(.004f, .004f, .004f));
        model = glm::rotate(model, (float)glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(100.f, -70.f, 0.f));
        founderShader.setUniformMat4f("model", model);

        founderTitanModel->Draw(founderShader);

        founderShader.unbind();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(static_cast<float>(yoffset));
}