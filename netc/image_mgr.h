#ifndef _IMAGE_MGR_H_
#define _IMAGE_MGR_H_

#include "utils/singleton.h"
#include "utils/zip_reader.h"

#include "render_base.h"
#include "render_util.h"

namespace ygopro
{
    
    struct CardTextureInfo {
		texi4 tex_info;
        uint16_t ref_block = 0;
	};
    
	class ImageMgr : public base::FrameBufferRenderer, public Singleton<ImageMgr> {
	public:
        ImageMgr() : base::FrameBufferRenderer(2048, 2048, false, false) {}
        
		texi4& GetCardTexture(uint32_t id);
        texi4& GetTexture(const std::string& name);
        base::Texture* LoadBigCardTexture(uint32_t id);
        base::Texture* GetRawCardTexture() { return render_tex; }
        base::Texture* GetRawMiscTexture() { return &misc_texture; }
        base::Texture* GetRawBGTexture() { return &bg_texture; }
        base::Texture* GetRawCardImage() { return &card_image; }
        texi4& GetCharTex(wchar_t ch);
        void UnloadCardTexture(uint32_t id);
		void UnloadAllCardTexture();
        
        uint16_t AllocBlock(uint32_t iid);
        bool FreeBlock(uint16_t, bool reserve);
        void IncreaseRef(uint16_t);
        
		void InitTextures(const std::string& image_path);
        void UninitTextures();
		bool LoadImageConfig();
        
    protected:
        std::unordered_map<uint32_t, CardTextureInfo> card_textures;
        std::unordered_map<std::string, texi4> misc_textures;
        std::array<texi4, 16> char_textures;
        std::list<uint16_t> unused_block;
        std::list<uint16_t> reserved_block;
        std::vector<std::pair<int32_t, uint32_t>> ref_count;
        std::unordered_map<uint32_t, std::list<uint16_t>::iterator> reserved_id;
        base::Texture misc_texture;
        base::Texture bg_texture;
        base::Texture card_image;
        ZipReader imageZip;
        std::shared_ptr<base::SimpleTextureRenderer> image_render;
	};

}

#endif
