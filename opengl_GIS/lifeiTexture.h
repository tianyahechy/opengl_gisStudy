#pragma once
namespace CELL
{
	class lifeiTexture
	{
	public:
		enum
		{
			TEXTURE_NONE,
			TEXTURE_1D,
			TEXTURE_2D,
			TEXTURE_3D
		};
	public:
		unsigned _texture;
		unsigned _texType;

	public:
		lifeiTexture( unsigned type = TEXTURE_NONE);
		virtual ~lifeiTexture();
	};

}

