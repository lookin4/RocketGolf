
#include <math.h>
#include "../GL/freeglut.h"
#include "shape.h"
#include "graphics_manager.h"


namespace lkn{

	// ここに書くべきではなけど一時的に
	#define M_PI (3.14159265358979)

    ShapeSP Shape::createSphere(const float r, const int stack, const int srice)
	{

        ShapeSP object = ShapeSP( new Shape() ) ;


		int v_size = ((srice + 1) * (stack + 1));
		int i_size = srice * stack * 6;
        object->vtxs = new Vec3[v_size];
        object->idxs = new unsigned int[i_size];

		// 頂点データを生成
		float radius = r;
		Vec3* vertex = object->vtxs;
		for (int i = 0; i <= stack; ++i) {
			float v = i / ((float)stack);
			float y = (float)(cosf(M_PI * v) * radius);
			float r = (float)(sinf(M_PI * v) * radius);
			for (int k = 0; k <= srice; ++k) {
				float u = k / ((float)srice);
				(*vertex).x = (cosf(2 * M_PI * u) * r);
				(*vertex).y = y;
				(*vertex).z = (sinf(2 * M_PI * u) * r);
				vertex++;
			}
		}

		// インデックスデータを生成
		unsigned int* index = object->idxs;
		for (int i = 0; i < stack; ++i) {
			int base = i * (srice + 1);
			for (int k = 0; k < srice; ++k) {
				*index++ = base + k;
				*index++ = base + k + 1;
				*index++ = base + k + (srice + 1);
				*index++ = base + k + (srice + 1);
				*index++ = base + k + 1;
				*index++ = base + k + 1 + (srice + 1);
			}
		}
        object->idx_num = i_size;

		GraphicsManager::getInstance()->addObject( object );

        return object;
	}



    ShapeSP Shape::createSquare(const float w, const float h, const int div)
    {

        ShapeSP object = ShapeSP( new Shape() );

        float size_x = w ;
        float size_z = h ;
        float sx = -(size_x * 0.5f);
        float sz = -(size_z * 0.5f);
        float wx = size_x / (float)div;
        float wz = size_z / (float)div;

        object->idx_num = div * div * 6 ;

        object->vtxs = new Vec3[ (div+1) * (div+1) ];
        object->idxs = new unsigned int[ object->idx_num ];


        for (int i = 0; i < div; i++)
        {
            for (int k = 0; k < div; k++)
            {
                float px = sx + (wx * (float)k);
                float py = sz + (wz * (float)i);

                object->vtxs[(i*div) + k].x = px;
                object->vtxs[(i*div) + k].y = py;
                object->vtxs[(i*div) + k].z = 0;

            }
        }

        // インデックスデータを生成
        unsigned int* index = object->idxs;
        for (int i = 0; i < div; ++i) {
            int base = i * (div + 1);
            for (int k = 0; k < div; ++k) {
                *index++ = base + k;
				*index++ = base + k + (div + 1);
                *index++ = base + k + 1;
                *index++ = base + k + 1;
				*index++ = base + k + (div + 1);
                *index++ = base + k + 1 + (div + 1);
            }
        }

        GraphicsManager::getInstance()->addObject(object);

        return object;
    }

	ShapeSP Shape::createTriangle(const float w, const float h, const int div) {
		ShapeSP object = ShapeSP(new Shape());



		return object;
	}

	void Shape::SettingColor(float r, float g, float b, float a) {
		m_color.x = r;
		m_color.y = g;
		m_color.z = b;
		m_color.a = a;
	};


	void Shape::updata(){

		

	}


	void Shape::render() const {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{

			glPushMatrix();

			glTranslatef(transform.pos.x, transform.pos.y, transform.pos.z);
			//glRotatef(transform.rot.x, 1.0f, 0.0f, 0.0f);
			//glRotatef(transform.rot.y, 0.0f, 1.0f, 0.0f);
			//glRotatef(transform.rot.z, 0.0f, 0.0f, 1.0f);
			glMultMatrixf((float*)&transform.rot);
			glScalef(transform.scl.x, transform.scl.y, transform.scl.z);


			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);

			glEnable(GL_DEPTH_TEST);

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, vtxs);

			if (nmls != nullptr) {
				glEnableClientState(GL_NORMAL_ARRAY);
				glNormalPointer(GL_FLOAT, 0, nmls);
			}

			if (texs != nullptr) {
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, m_texture->image_id);
				glTexCoordPointer(2,GL_FLOAT,0,texs);
			}
			float sColor[] = { m_color.x, m_color.y, m_color.z,m_color.a };
			//glColor3f(m_color.x, m_color.y, m_color.z);
			glMaterialfv(GL_FRONT,GL_DIFFUSE,sColor);

			glDrawElements(GL_TRIANGLES, idx_num, GL_UNSIGNED_INT, idxs);

			glPopMatrix();
		}
		glPopAttrib();
	}

}
