#include "OGLFrameBuffer.h"
#include "Utils\Logger.h"   

namespace Engine
{
    OGLFrameBuffer::OGLFrameBuffer(unsigned int width, unsigned int height)
    {
        glGenFramebuffers(1, &mID);
        glBindFramebuffer(GL_FRAMEBUFFER, mID);

        glGenTextures(1, &mTexture);
        glBindTexture(GL_TEXTURE_2D, mTexture);

        Logger::LogWarn("tex id", mTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            Logger::LogWarn("fb incomplete");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    OGLFrameBuffer::~OGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &mID);
    }

    void OGLFrameBuffer::Load()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mID);

        //TODO : Create a class for all render commands
        glClearColor(0.180392161f, 0.545098066f, 0.341176480f, 1.000000000f);
        //glClearColor(0.0f, 0.4f, 0.4f, 1.000000000f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OGLFrameBuffer::Unload()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}