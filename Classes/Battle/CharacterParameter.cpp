#include "CharacterParameter.h"

//character1
const std::string CharacterParameter::character1_resource = "Character/monster1.png";
const float CharacterParameter::character1_mass= 500 ;
const int CharacterParameter::character1_maxHealth= 100 ;
const float CharacterParameter::character1_restitution= 1 ;

//character2
const std::string CharacterParameter::character2_resource = "Character/monster2.png";
const float CharacterParameter::character2_mass= 750 ;
const int CharacterParameter::character2_maxHealth= 80 ;
const float CharacterParameter::character2_restitution= 0.6 ;


std::string CharacterParameter::getResource(GameSetting::Character character){
	switch (character)
	{
	case GameSetting::Character::CHARACTER1:
		return character1_resource;
		break;
	case GameSetting::Character::CHARACTER2:
		return character2_resource;
		break;
	}
}


float CharacterParameter::getMass(GameSetting::Character character){
	switch (character)
	{
	case GameSetting::Character::CHARACTER1:
		return character1_mass;
		break;
	case GameSetting::Character::CHARACTER2:
		return character2_mass;
		break;
	}

}


int CharacterParameter::getMaxHealth(GameSetting::Character character){
	switch (character)
	{
	case GameSetting::Character::CHARACTER1:
		return character1_maxHealth;
		break;
	case GameSetting::Character::CHARACTER2:
		return character2_maxHealth;
		break;
	}
}


float CharacterParameter::getRestitution(GameSetting::Character character){
	switch (character)
	{
	case GameSetting::Character::CHARACTER1:
		return character1_restitution;
		break;
	case GameSetting::Character::CHARACTER2:
		return character2_restitution;
		break;
	}
}