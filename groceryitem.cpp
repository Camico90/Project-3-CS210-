#include "GroceryItem.h"

// Constructs a GroceryItem object using a member initializer list
GroceryItem::GroceryItem(const std::string& name, int quantity)
    : itemName(name), itemQuantity(quantity) {
    // Body is empty because all initialization is done in the initializer list
}

// Returns the name of the grocery item. It's a const method because it doesn't modify the object
std::string GroceryItem::getName() const {
    return itemName;
}

// Returns the current quantity of the grocery item
int GroceryItem::getQuantity() const {
    return itemQuantity;
}

// Increments the item's quantity by 1
void GroceryItem::addQuantity() {
    ++itemQuantity;
}

// Decreases the item's quantity by 1
void GroceryItem::subtractQuantity() {
    // This check is crucial to ensure the quantity never becomes negative
    if (itemQuantity > 0) {
        // Uses the pre-decrement operator
        --itemQuantity;
    }
}
