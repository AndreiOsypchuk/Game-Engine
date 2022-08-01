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

            m_VBO = std::make_shared<GE::VertexBufferObject>(&vertices, sizeof(vertices));



            GE::VertexSpec TriangleVertexSpec(
            {
                {GE::VertexDataType::Float3, "a_Position"}, 
                {GE::VertexDataType::Float3, "a_Colors"}
            });

            TriangleVertexSpec.AttachVertexBuffer(m_VBO);
            TriangleVertexSpec.GenAttributes();

            // Then vertex spec is passed to the renderer and renderer is making
            // a draw call

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

        std::shared_ptr<GE::Shader> m_Shader;
        std::shared_ptr<GE::VertexBufferObject> m_VBO;

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
