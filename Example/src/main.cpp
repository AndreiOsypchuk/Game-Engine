#include <GameEngine>
#include <glad/glad.h>

class TestLayer : public GE::Layer
{
    public:


        TestLayer()
        {

            float vertices[] = {
                -0.5f, 0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
            };

            unsigned int indices[] = {
                0, 1, 2, 2, 3, 0
            };

            m_Shader = std::make_shared<GE::Shader>("shader.glsl");

            m_VBO = std::make_shared<GE::VertexBufferObject>(&vertices, sizeof(vertices));
            m_VIO = std::make_shared<GE::VertexIndexObject>(&indices, sizeof(indices));



            GE::VertexSpec TriangleVertexSpec(
            {
                {GE::VertexDataType::Float3, "a_Position"}, 
            });

            TriangleVertexSpec.AttachVertexBuffer(m_VBO);
            TriangleVertexSpec.AttachIndexBuffer(m_VIO);
            TriangleVertexSpec.GenAttributes();

        }

        void OnEvent(GE::Event& e) override
        {
        }

        void OnUpdate(float time) override
        {

            // Renderer::Scene(m_Camera, light);
            // Renderer::Draw(GE_CUBE, m_Shader, glm::vec3 position);

            m_Shader->Use();
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

    public:

        std::shared_ptr<GE::Shader> m_Shader;
        std::shared_ptr<GE::VertexBufferObject> m_VBO;
        std::shared_ptr<GE::VertexIndexObject> m_VIO;

};

class Example : public GE::Application
{
    public:
        Example() {
            GE_INFO("Is Running");
            PushLayer(new TestLayer);

        };

        ~Example() {};
};

GE::Application* GE::CreateApplication()
{
    return new Example();
}
