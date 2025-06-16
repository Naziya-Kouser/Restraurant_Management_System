# Restraurant_Management_System
A C-based Restaurant Management System with admin and customer interfaces, order placement, billing, and tracking features. Includes file handling, dynamic linked lists, mini-games, and recipe viewing. Enhances user engagement with an interactive console-based UI.



# main()
Initializes the food menu using createadmin() and handles the main navigation to admin, customer, or games modules based on user input.

# admin()
Admin interface to manage food items: view sales, add/delete menu items, or view the entire menu. Also calculates and displays profit from each item.

# customer()
Allows customers to place, review, delete, and finalize orders. Includes delivery tracking animation and billing calculation.

# games()
Interactive mini-game section with options to play:

Number guessing

Word guessing

Recipe guessing
Winning reveals fun food recipes for the user.

# showRecipes(int recipeId)
Displays a detailed recipe for a food item. Called after successfully completing a mini-game. Each recipeId corresponds to a specific recipe, showing ingredients and preparation steps.

# deleteList(struct node* head)
Deallocates memory of a doubly linked list (used for clearing orders). Traverses the list and frees each node properly to avoid memory leaks.

# createadmin(), createcustomer()
Used to dynamically create new nodes for the admin menu or customer orders, storing item name, quantity, and price in a linked list.

# displayList(struct node* head)
Prints all items in the passed list—used for displaying the admin food menu and customer’s cart.

# deleteadmin() / deletecustomer()
Remove items from the admin food list or customer order list based on serial numbers entered.

# calculatetotsales()
Calculates profit by subtracting total cost from selling price and stores it in a separate sales list (head_s).

# displaybill()
Prints the customer’s final bill with item names, quantities, and total cost after placing the order.

# animateStatus()
Displays animation effects for the current order status (e.g., loading dots) for visual appeal in console.

# animateStatusTransition()
Transitions between order statuses ("Ordered" → "Shipped" → "Delivered") using animated delays.

# updateOrderStatus(Order *order, const char *newStatus)
Updates the status of a user's order during tracking.

# displayOrder(Order order)
Displays current status of the user’s order in a structured format during tracking.
