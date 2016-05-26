#ifndef LKN_SAHPE_H
#define LKN_SAHPE_H


#include <memory>
#include "transform.h"
#include "camera.h"
#include "vector2.h"
#include "vector4.h"
#include "image.h"


namespace lkn{

    class Shape;
    typedef std::shared_ptr< Shape > ShapeSP;

	class Shape{
	protected :

        // デフォルトコンストラクタで各メンバの初期化
        Shape():
        vtxs(nullptr),
        idxs(nullptr),
        idx_num(0),
		nmls(nullptr),
		texs(nullptr),
		m_color(1.0f, 1.0f, 1.0f,1.0f)
        {};

	public:

        ~Shape() {
            //printf("シェイプが削除されました\n");
        }

        static ShapeSP createSphere(const float r, const int stack, const int srice);
        static ShapeSP createSquare(const float w, const float h, const int div);

		static ShapeSP createTriangle(const float w, const float h, const int div);

		void SettingColor(float r, float g, float b, float a);

        Transform transform;

		Vec3 *vtxs;
		unsigned int *idxs ;
		unsigned int idx_num;

		Vec3 *nmls;

		Vec2 *texs;

		Image *m_texture;

		Vec4 m_color;

		float radius;

		void updata() ;
		void render() const;

	};
}


#endif