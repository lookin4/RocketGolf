#ifndef GAME_CAHRACTER_H
#define GAME_CAHRACTER_H
#include <memory>
#include "../lkn_engine/game_object.h"
#include "../lkn_library/shape.h"
#include "../lkn_library/x_file.h"
#include "../lkn_library/graphics_manager.h"
#include "../lkn_library/sequence.h"


namespace game {

class Character;
typedef std::shared_ptr< Character > CharacterSP;
typedef std::weak_ptr< Character > CharacterWP;

class Character : public lkn::GameObject {
private :

    Character(){
        _sequence.change( &Character::seqIdle );

		const float MM_PI = 3.14f;
		transform.rot = glm::rotate(transform.rot, MM_PI / 180 * -90.0f, glm::vec3(1, 0, 0));

		dodai = lkn::XFile::createXFile( "X_File/dodai.x" ,nullptr);
		//body = lkn::Shape::createSphere(500,500,4);
		dodai->transform = transform;
		dodai->SettingColor(0.3f, 0.3f, 0.3f, 1.0f);

		houdai = lkn::XFile::createXFile("X_File/houdai.x", nullptr);
		//body = lkn::Shape::createSphere(500,500,4);
		
		houdai->transform = transform;

		houdai_offset = { 0,0,0 };
		
		houdai->transform.pos.x = dodai->transform.pos.x + houdai_offset.x;
		houdai->transform.pos.y = dodai->transform.pos.y + houdai_offset.y;
		houdai->transform.pos.z = dodai->transform.pos.z + houdai_offset.z;
		houdai->SettingColor(1.0f, 0.2f, 0.2f, 1.0f);
    }
public :
    static CharacterSP create();

    lkn::ShapeSP dodai;
	lkn::ShapeSP houdai;
	lkn::Vec3 houdai_offset;

	glm::mat4x4 houdai_rotate;

    CharacterWP my_weak ;

    lkn::Sequence< Character > _sequence;

    void seqIdle( float delta );
    void seqMove( float delta );

    virtual void updata();


};

}

//class UI {
//    static void func( CharacterSP );
//};

#endif