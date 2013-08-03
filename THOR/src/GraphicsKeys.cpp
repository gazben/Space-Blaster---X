/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011-2012 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

#include <Thor/Resources/GraphicsKeys.hpp>
#include <Thor/Detail/ResourceKeyHelpers.hpp>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Font.hpp>


namespace thor
{
namespace
{

	// Functor to call sf::Image::Create() overload for size and fillColor
	struct ImageFromSize
	{
		ImageFromSize(unsigned int width, unsigned int height, const sf::Color& fillColor)
		: width(width)
		, height(height)
		, fillColor(fillColor)
		{
		}

		bool operator() (sf::Image& image)
		{
			image.Create(width, height, fillColor);
			return true;
		}

		unsigned int width;
		unsigned int height;
		sf::Color fillColor;
	};

	// Functor to call sf::Image::Create() overload for pixels
	struct ImageFromPixels
	{
		ImageFromPixels(unsigned int width, unsigned int height, const sf::Uint8* pixels)
		: width(width)
		, height(height)
		, pixels(pixels)
		{
		}

		bool operator() (sf::Image& image)
		{
			image.Create(width, height, pixels);
			return true;
		}

		unsigned int width;
		unsigned int height;
		const sf::Uint8* pixels;
	};

} // namespace

// ---------------------------------------------------------------------------------------------------------------------------


namespace Resources
{

	ImageKey::ImageKey()
	{
	}

	ImageKey ImageKey::FromSize(unsigned int width, unsigned int height, const sf::Color& fillColor, const std::string& tag)
	{
		ImageKey tmp;
		tmp.mLoader =	ImageFromSize(width, height, fillColor);
		tmp.mKey =		detail::Tagger("Size") << width << height << fillColor << tag;
		return tmp;
	}

	ImageKey ImageKey::FromFile(const std::string& fileName, const std::string& tag)
	{
		ImageKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Image::LoadFromFile, _1, fileName);
		tmp.mKey =		detail::Tagger("File") << fileName << tag;
		return tmp;
	}

	ImageKey ImageKey::FromMemory(const void* data, std::size_t size, const std::string& tag)
	{
		ImageKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Image::LoadFromMemory, _1, data, size);
		tmp.mKey =		detail::Tagger("Memory") << data << size << tag;
		return tmp;
	}

	ImageKey ImageKey::FromPixels(unsigned int width, unsigned int height, const sf::Uint8* pixels, const std::string& tag)
	{
		ImageKey tmp;
		tmp.mLoader =	ImageFromPixels(width, height, pixels);
		tmp.mKey =		detail::Tagger("Pixels") << width << height << pixels << tag;
		return tmp;
	}
	
	ImageKey ImageKey::FromStream(sf::InputStream& stream, const std::string& tag)
	{
		ImageKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Image::LoadFromStream, _1, tr1::ref(stream));
		tmp.mKey =		detail::Tagger("Stream") << &stream << tag;
		return tmp;
	}

	MovedPtr<sf::Image, NoCopy> ImageKey::Load() const
	{
		return detail::LoadResource(mLoader);
	}

	void ImageKey::Swap(ImageKey& other)
	{
		swap(mLoader,	other.mLoader);
		swap(mKey,		other.mKey);
	}

	bool operator< (const ImageKey& lhs, const ImageKey& rhs)
	{
		return detail::GetKeyInfo(lhs) < detail::GetKeyInfo(rhs);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	TextureKey::TextureKey()
	{
	}

	TextureKey TextureKey::FromSize(unsigned int width, unsigned int height, const std::string& tag)
	{
		TextureKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Texture::Create, _1, width, height);
		tmp.mKey =		detail::Tagger("Size") << width << height << tag;
		return tmp;
	}

	TextureKey TextureKey::FromFile(const std::string& fileName, const sf::IntRect& area, const std::string& tag)
	{
		TextureKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Texture::LoadFromFile, _1, fileName, area);
		tmp.mKey =		detail::Tagger("File") << fileName << tag;
		return tmp;
	}

	TextureKey TextureKey::FromMemory(const void* data, std::size_t size, const sf::IntRect& area, const std::string& tag)
	{
		TextureKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Texture::LoadFromMemory, _1, data, size, area);
		tmp.mKey =		detail::Tagger("Memory") << data << size << ToString(area) << tag;
		return tmp;
	}

	TextureKey TextureKey::FromImage(const sf::Image& image, const sf::IntRect& area, const std::string& tag)
	{
		TextureKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Texture::LoadFromImage, _1, tr1::cref(image), area);
		tmp.mKey =		detail::Tagger("Image") << &image << ToString(area) << tag;
		return tmp;
	}

	TextureKey TextureKey::FromStream(sf::InputStream& stream, const sf::IntRect& area, const std::string& tag)
	{
		TextureKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Texture::LoadFromStream, _1, tr1::ref(stream), area);
		tmp.mKey =		detail::Tagger("Stream") << &stream << ToString(area) << tag;
		return tmp;
	}

	MovedPtr<sf::Texture, NoCopy> TextureKey::Load() const
	{
		return detail::LoadResource(mLoader);
	}

	void TextureKey::Swap(TextureKey& other)
	{
		swap(mLoader,	other.mLoader);
		swap(mKey,		other.mKey);
	}

	bool operator< (const TextureKey& lhs, const TextureKey& rhs)
	{
		return detail::GetKeyInfo(lhs) < detail::GetKeyInfo(rhs);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	ShaderKey::ShaderKey()
	{
	}

	ShaderKey ShaderKey::FromFile(const std::string& fileName, unsigned int shaderType, const std::string& tag)
	{
		// Note:
		// - Use unsigned int instead of sf::Shader::Type to avoid #include of Shader header in GraphicsKeys.hpp
		// - Explicitly declare function pointer to resolve overload ambiguity
		bool (sf::Shader::*fnPtr)(const std::string&, sf::Shader::Type) = &sf::Shader::LoadFromFile;

		ShaderKey tmp;
		tmp.mLoader =	tr1::bind(fnPtr, _1, fileName, static_cast<sf::Shader::Type>(shaderType));
		tmp.mKey =		detail::Tagger("File") << fileName << shaderType << tag;
		return tmp;
	}

	ShaderKey ShaderKey::FromFile(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename, const std::string& tag)
	{
		bool (sf::Shader::*fnPtr)(const std::string&, const std::string&) = &sf::Shader::LoadFromFile;

		ShaderKey tmp;
		tmp.mLoader =	tr1::bind(fnPtr, _1, vertexShaderFilename, fragmentShaderFilename);
		tmp.mKey =		detail::Tagger("File") << vertexShaderFilename << fragmentShaderFilename << tag;
		return tmp;
	}	

	ShaderKey ShaderKey::FromMemory(const std::string& shaderCode, unsigned int shaderType, const std::string& tag)
	{
		bool (sf::Shader::*fnPtr)(const std::string&, sf::Shader::Type) = &sf::Shader::LoadFromMemory;

		ShaderKey tmp;
		tmp.mLoader =	tr1::bind(fnPtr, _1, shaderCode, static_cast<sf::Shader::Type>(shaderType));
		tmp.mKey =		detail::Tagger("Memory") << shaderCode << shaderType << tag;
		return tmp;
	}

	ShaderKey ShaderKey::FromMemory(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& tag)
	{
		bool (sf::Shader::*fnPtr)(const std::string&, const std::string&) = &sf::Shader::LoadFromMemory;

		ShaderKey tmp;
		tmp.mLoader =	tr1::bind(fnPtr, _1, vertexShaderCode, fragmentShaderCode);
		tmp.mKey =		detail::Tagger("Memory") << vertexShaderCode << fragmentShaderCode << tag;
		return tmp;
	}

	ShaderKey ShaderKey::FromStream(sf::InputStream& stream, unsigned int shaderType, const std::string& tag)
	{
		bool (sf::Shader::*fnPtr)(sf::InputStream&, sf::Shader::Type) = &sf::Shader::LoadFromStream;

		ShaderKey tmp;
		tmp.mLoader =	tr1::bind(fnPtr, _1, tr1::ref(stream), static_cast<sf::Shader::Type>(shaderType));
		tmp.mKey =		detail::Tagger("Stream") << &stream << shaderType << tag;
		return tmp;
	}
	
	ShaderKey ShaderKey::FromStream(sf::InputStream& vertexShaderStream, sf::InputStream& fragmentShaderStream, const std::string& tag)
	{
		bool (sf::Shader::*fnPtr)(sf::InputStream&, sf::InputStream&) = &sf::Shader::LoadFromStream;

		ShaderKey tmp;
		tmp.mLoader =	tr1::bind(fnPtr, _1, tr1::ref(vertexShaderStream), tr1::ref(fragmentShaderStream));
		tmp.mKey =		detail::Tagger("Stream") << &vertexShaderStream << &fragmentShaderStream << tag;
		return tmp;
	}

	MovedPtr<sf::Shader, NoCopy> ShaderKey::Load() const
	{
		return detail::LoadResource(mLoader);
	}

	void ShaderKey::Swap(ShaderKey& other)
	{
		swap(mLoader,	other.mLoader);
		swap(mKey,		other.mKey);
	}

	bool operator< (const ShaderKey& lhs, const ShaderKey& rhs)
	{
		return detail::GetKeyInfo(lhs) < detail::GetKeyInfo(rhs);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	FontKey::FontKey()
	{
	}

	FontKey FontKey::FromFile(const std::string& fileName, const std::string& tag)
	{
		FontKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Font::LoadFromFile, _1, fileName);
		tmp.mKey =		detail::Tagger("File") << fileName << tag;
		return tmp;
	}

	FontKey FontKey::FromMemory(const void* data, std::size_t size, const std::string& tag)
	{
		FontKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Font::LoadFromMemory, _1, data, size);
		tmp.mKey =		detail::Tagger("Memory") << data << size << tag;
		return tmp;
	}

	FontKey FontKey::FromStream(sf::InputStream& stream, const std::string& tag)
	{
		FontKey tmp;
		tmp.mLoader =	tr1::bind(&sf::Font::LoadFromStream, _1, tr1::ref(stream));
		tmp.mKey =		detail::Tagger("Stream") << &stream << tag;
		return tmp;
	}

	MovedPtr<sf::Font, NoCopy> FontKey::Load() const
	{
		return detail::LoadResource(mLoader);
	}

	void FontKey::Swap(FontKey& other)
	{
		swap(mLoader,	other.mLoader);
		swap(mKey,		other.mKey);
	}

	bool operator< (const FontKey& lhs, const FontKey& rhs)
	{
		return detail::GetKeyInfo(lhs) < detail::GetKeyInfo(rhs);
	}

} // namespace Resources
} // namespace thor
