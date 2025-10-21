#ifndef GROCERYITEM_H
#define GROCERYITEM_H

#include <string>

// Defines the structure for a single grocery item, encapsulating its data
class GroceryItem {
public:
    // Constructs a GroceryItem object
    GroceryItem(const std::string& name, int quantity = 1);

    // Gets and returns name of item
    std::string getName() const;

    // Gets and returns quantity of item
    int getQuantity() const;

    // Increments the item's quantity by one
    void addQuantity();

    // Decrements the item's quantity by one
    void subtractQuantity();

private:
    std::string itemName;
    int itemQuantity;
};

#endif // GROCERYITEM_H
