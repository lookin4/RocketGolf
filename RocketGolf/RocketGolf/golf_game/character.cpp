#include "character.h"
#include "../lkn_library/input_manager.h"
#include"../glm/gtc/matrix_transform.hpp"

const float MM_PI = 3.14f;

namespace game {

CharacterSP Character::create() {

    CharacterSP object = CharacterSP( new Character() );

    object->my_weak = object;

	printf("キャラクタが生成されました\n");

    return object;

}

void Character::seqIdle(float delta) {
    if (0.0f == _sequence.getTime()) {
        printf( "キャラクタアイドリングシーケンス初期化\n" );
    }

    if (0.5f < _sequence.getTime()) {
        _sequence.change( &Character::seqMove );
    }

}

void Character::seqMove(float delta) {

    if (0.0f == _sequence.getTime()) {
        printf("キャラクタムーブシーケンス初期化\n");
    }

    //transform.pos.x += 1.0f;

	//dodai->transform.rot.x += 1;


	if (lkn::InputManager::getInstance()->keyPlessAndHold('a')) {
		dodai->transform.rot = glm::rotate(dodai->transform.rot, MM_PI / 180 * 1.0f, glm::vec3(0, 0, 1));
		//houdai->transform.rot = glm::rotate(houdai->transform.rot, MM_PI / 180 * 1.0f, glm::vec3(0, 1, 0));
	}
	if (lkn::InputManager::getInstance()->keyPlessAndHold('d')) {
		dodai->transform.rot = glm::rotate(dodai->transform.rot, MM_PI / 180 * -1.0f, glm::vec3(0, 0, 1));
		//houdai->transform.rot = glm::rotate(houdai->transform.rot, MM_PI / 180 * -1.0f, glm::vec3(0, 1, 0));
		//dodai->transform.pos.x += 0.1f;
	}
	if (lkn::InputManager::getInstance()->keyPlessAndHold('w')) {
		houdai_rotate = glm::rotate(houdai_rotate, MM_PI / 180 * 1.0f, glm::vec3(1, 0, 0));
		//transform.rot = glm::rotate(transform.rot, MM_PI / 180 * 1.0f, glm::vec3(1, 0, 0));
	}
	if (lkn::InputManager::getInstance()->keyPlessAndHold('s')) {
		//transform.rot.x -= 1;
		houdai_rotate = glm::rotate(houdai_rotate, MM_PI / 180 * -1.0f, glm::vec3(1, 0, 0));
		//transform.rot = glm::rotate(transform.rot, MM_PI / 180 * -1.0f, glm::vec3(1, 0, 0));
	}

	//dodai->transform.rot = transform.rot;
	houdai->transform.rot = dodai->transform.rot * houdai_rotate;
	//houdai->transform.rot = dodai->transform.rot * transform.rot;

	houdai->transform.pos.x = dodai->transform.pos.x + houdai_offset.x;
	houdai->transform.pos.y = dodai->transform.pos.y + houdai_offset.y;
	houdai->transform.pos.z = dodai->transform.pos.z + houdai_offset.z;


	//glm::vec3 z = { sin(_yaw), 0, cos(_yaw) }; // 仮のベクトル
	//glm::vec3 y = nor; // 三角形の法線を取ってくる
	//glm::vec3 x = cross(y, z);
	//z = cross(x, y);


	//Mat4x4 mat = Mat4x4(
	//	x.x, x.y, x.z, 0,
	//	y.x, y.y, y.z, 0,
	//	z.x, z.y, z.z, 0,
	//	0, 0, 0, 1);
	
	glm::mat4x4 wm = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	//houdai->transform.rot = dodai->transform.rot;

	


	//houdai->transform.rot.z = transform.rot.z;

	//houdai->transform.rot.x = transform.rot.x;

    /*if (100.0f < transform.pos.x) {
        life_count = 0;
    }*/

}


void Character::updata() {

    _sequence.run( this, 1.0f / 60.0f );

}


}