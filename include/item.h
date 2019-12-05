/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
  @author Jared Sisco, <j.sisco@uleth.ca>
* @date 2019-11
*/

#ifndef INCLUDE_ITEM_H_
#define INCLUDE_ITEM_H_

/**
* A class used to implement all items
*/

#include <string>

/**
* An enum to indicate what the item's intended function is
*/
enum ItemType {I_NULL, I_Spare_Part, I_Cargo_Key, I_Safe_Code,
               I_Hand_Warmer, I_Coffee_Mug, ItemType_MAX
              };

/**
* Struct that contains all properties of an item
* Used to initialize items
*/
struct Item_Data {
  ItemType type;
  std::string item_name;
  std::string use_text;
  std::string description;

  Item_Data(ItemType Type, const std::string &item_name,
            const std::string & txt, const std::string &des) :
    type(Type), item_name(item_name), use_text(txt), description(des) {}
  Item_Data() {}
};

class Item {
 public:
  /**
  * Default Constructor
  * @param
  */
  explicit Item(ItemType Needed_Type);

  /**
  *
  */
  static Item_Data get_Properties(ItemType Needed_Type);

  /**
  * Default destructor
  */
  virtual ~Item();

  /**
  * Access the name of the Item
  * @return The name of the Item as a string
  */
  std::string getId() const;

  /**
  * Access the description of the Item
  * @return The description of the Item as a String
  */
  std::string getDescription() const;

  /**
  * Access the ItemType if the Item
  * @return The type as an ItemType enum
  */
  ItemType getType() const;

  /**
  * Access the activation description if the Item
  * @return The activation description as an string
  */
  std::string getAct() const;

 private:
  // Name of item
  Item_Data Item_Properties;
};

#endif  // INCLUDE_ITEM_H_
