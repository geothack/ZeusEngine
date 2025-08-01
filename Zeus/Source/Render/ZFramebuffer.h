#pragma once

class ZFramebuffer
{
public:
	ZFramebuffer();

	void Init();

	void Attach() const;
	void Detach() const;

	void Render(bool doRender = true);

	uint32_t GetTexture() { return z_Texture; }

private:
	ZArrayObject z_ArrayObject{};
	uint32_t z_Framebuffer{};
	uint32_t z_Texture{};

};

