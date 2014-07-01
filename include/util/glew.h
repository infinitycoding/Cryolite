#include <GL/glew.h>

class GLEW
{
	public:
		GLEW();
		~GLEW();

		GLenum loadingSuccess();
		const unsigned char *getVersion();

		bool checkExtention(const char *name);


    protected:
        const unsigned char *version;
        GLenum error;
};
