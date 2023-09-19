#include <iostream>
#include "cyaml/cyaml.h"

std::string yaml_str = R"(
rifleman:
  parser: cyberband::SoldierInfo
  attributes:
    parser: cyberband::AttributesInfo
    max_move_hspeed: 3.968
    max_rotate_hspeed: 90
    max_hp: 78
    max_load: 9
    category: Rifleman
  model: 
    parser: cyberband::BodyInfo
    name: models/humans/human_golden_1.8m.pb
  motion:
    parser: cyberband::HumanMotionInfo
  equip:
    parser: cyberband::HumanEquipCtrlInfo
    equipments:
      - bodyarmor_ii
      - ak47
    clips:
      m43_7.62x39: 6
  behavior: 
    parser: cyberband::BehaviorInfo
    tree: bt_soldier::Rifleman
    interval: 0.5
  cmd:
    parser: cyberband::CmdMgrInfo
    interval: 3.0
  emotion:
    parser: cyberband::EmotionInfo
    fear_coef: 0.5
    fear_attack:
      min: 0.05
      max: 0.15
    fear_decay: 
      min: 0.0
      max: 0.2
    interval: 1.0
  observer:
    parser: cyberband::ObserverInfo
    interval: 0.5
    history_timeout: 30
    eye:
      parser: cyberband::EyeInfo
      mount_point: view_point
      radius: 230.94010767585024
      height: 400
      flip: true
      direction: 
        x: 0
        y: 0
        z: 1
      center:
        x: 0
        y: 0
        z: 200
      interval: 0

sniper: 
  parser: cyberband::SoldierInfo
  attributes:
    parser: cyberband::AttributesInfo
    max_move_hspeed: 3.968
    max_rotate_hspeed: 90
    max_hp: 78
    max_load: 9
    category: Rifleman
  model: 
    parser: cyberband::BodyInfo
    name: models/humans/human_golden_1.8m.pb
  motion:
    parser: cyberband::HumanMotionInfo
  equip:
    parser: cyberband::HumanEquipCtrlInfo
    equipments:
      - bodyarmor_ii
      - svd
    clips:
      rimmed_7.62x54: 3 
  behavior: 
    parser: cyberband::BehaviorInfo
    tree: bt_soldier::Rifleman
    interval: 0.5
  cmd:
    parser: cyberband::CmdMgrInfo
    interval: 3.0
  emotion:
    parser: cyberband::EmotionInfo
    fear_coef: 0.5
    fear_attack:
      min: 0.05
      max: 0.15
    fear_decay: 
      min: 0.0
      max: 0.2
    interval: 1.0
  observer:
    parser: cyberband::ObserverInfo
    interval: 0.5
    history_timeout: 30
    eye:
      parser: cyberband::EyeInfo
      mount_point: view_point
      radius: 230.94010767585024
      height: 400
      flip: true
      direction: 
        x: 0
        y: 0
        z: 1
      center:
        x: 0
        y: 0
        z: 200
      interval: 0

machine_gunner: 
  parser: cyberband::SoldierInfo
  attributes:
    parser: cyberband::AttributesInfo
    max_move_hspeed: 3.968
    max_rotate_hspeed: 90
    max_hp: 78
    max_load: 9
    category: Rifleman
  model: 
    parser: cyberband::BodyInfo
    name: models/humans/human_golden_1.8m.pb
  motion:
    parser: cyberband::HumanMotionInfo
  equip:
    parser: cyberband::HumanEquipCtrlInfo
    equipments:
      - bodyarmor_ii
      - machine_gun_89
      - pistol_54
    clips:
      nato_12.7x99: 3
      tokarev_7.62x25: 3
  behavior: 
    parser: cyberband::BehaviorInfo
    tree: bt_soldier::Rifleman
    interval: 0.5
  cmd:
    parser: cyberband::CmdMgrInfo
    interval: 3.0
  emotion:
    parser: cyberband::EmotionInfo
    fear_coef: 0.5
    fear_attack:
      min: 0.05
      max: 0.15
    fear_decay: 
      min: 0.0
      max: 0.2
    interval: 1.0
  observer:
    parser: cyberband::ObserverInfo
    interval: 0.5
    history_timeout: 30
    eye:
      parser: cyberband::EyeInfo
      mount_point: view_point
      radius: 230.94010767585024
      height: 400
      flip: true
      direction: 
        x: 0
        y: 0
        z: 1
      center:
        x: 0
        y: 0
        z: 200
      interval: 0


bot_controller:
  parser: cyberband::SoldierInfo
  attributes:
    parser: cyberband::AttributesInfo
    max_move_hspeed: 3.968
    max_rotate_hspeed: 90
    max_hp: 78
    max_load: 9
    category: Rifleman
  model: 
    parser: cyberband::BodyInfo
    name: models/humans/human_golden_1.8m.pb
  motion:
    parser: cyberband::HumanMotionInfo
  equip:
    parser: cyberband::HumanEquipCtrlInfo
    equipments:
      - bodyarmor_ii
      - huawei_pad
  behavior: 
    parser: cyberband::BehaviorInfo
    tree: bt_soldier::BotCtrl
    interval: 0.5
  cmd:
    parser: cyberband::CmdMgrInfo
    interval: 3.0
  emotion:
    parser: cyberband::EmotionInfo
    fear_coef: 0.5
    fear_attack:
      min: 0.05
      max: 0.15
    fear_decay: 
      min: 0.0
      max: 0.2
    interval: 1.0
  observer:
    parser: cyberband::ObserverInfo
    interval: 0.5
    history_timeout: 30
    eye:
      parser: cyberband::EyeInfo
      mount_point: view_point
      radius: 230.94010767585024
      height: 400
      flip: true
      direction: 
        x: 0
        y: 0
        z: 1
      center:
        x: 0
        y: 0
        z: 200
      interval: 0



shootman:
  parser: cyberband::SoldierInfo
  attributes:
    parser: cyberband::AttributesInfo
    max_move_hspeed: 3.968
    max_rotate_hspeed: 90
    max_hp: 78
    max_load: 9
    category: Shootman
  model: 
    parser: cyberband::BodyInfo
    name: models/humans/human_golden_1.8m.pb
  motion:
    parser: cyberband::HumanMotionInfo
  equip:
    parser: cyberband::HumanEquipCtrlInfo
    equipments:
      - bodyarmor_ii
      - ak47
    clips:
      m43_7.62x39: 3
  observer:
    parser: cyberband::ObserverInfo
    interval: 0.5
    history_timeout: 30
    eye:
      parser: cyberband::EyeInfo
      mount_point: view_point
      radius: 230.94010767585024
      height: 400
      flip: true
      direction: 
        x: 0
        y: 0
        z: 1
      center:
        x: 0
        y: 0
        z: 200
      interval: 0
      
bodyarmor_ii: 
  parser: cyberband::ArmorInfo
  defense_priority: 10
  defense_value: 554.47
  mass: 10
  slots:
    - Armor

bodyarmor_iii: 
  parser: cyberband::ArmorInfo
  defense_priority: 10
  defense_value: 3341.16
  mass: 10
  slots:
    - Armor
)";

int main() {

  cyaml::Parser parser;
  cyaml::Document doc;

  if(!parser.parse(yaml_str, doc)) {
    std::cerr << "failed to parse yaml" << std::endl;
  }

  return 0;
}