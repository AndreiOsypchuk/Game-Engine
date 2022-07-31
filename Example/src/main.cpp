#include <GameEngine>
#include <glad/glad.h>

class TestLayer : public GE::Layer
{
    public:


        TestLayer()
        {
            float vertices[] = {
                0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
                0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
            };

            m_Shader = std::make_shared<GE::Shader>("shader.glsl");

            GE::VertexSpec TriangleVertexSpec(
            {&vertices, sizeof(vertices)},
            {
                {GE::VertexDataType::Float3, "a_Position"}, 
                {GE::VertexDataType::Float3, "a_Colors"}
            });


            TriangleVertexSpec.GenAttrib();

        }

        void OnEvent(GE::Event& e) override
        {
        }

        void OnUpdate(float time) override
        {
            m_Shader->Use();
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

    public:

        uint32_t m_VAO;
        uint32_t m_VBO;
        std::shared_ptr<GE::Shader> m_Shader;

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
