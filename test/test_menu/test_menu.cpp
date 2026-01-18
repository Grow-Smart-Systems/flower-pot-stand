#include <unity.h>
#include "../../src/Screen/Menu/Menu.h"
#include "../../src/Screen/Menu/MenuItem.h"

// ============ Menu Tests ============

void test_menu_initial_state() {
    Menu menu;
    TEST_ASSERT_EQUAL(0, menu.GetMenuItemsSize());
    TEST_ASSERT_EQUAL(0, menu.GetCurrentIndex());
    TEST_ASSERT_EQUAL(DisplayMenu::SUB_MENU, menu.GetDisplayMenu());
}

void test_menu_add_item() {
    Menu menu;
    MenuItem item("Test Item");
    
    menu.AddMenuItem(item);
    
    TEST_ASSERT_EQUAL(1, menu.GetMenuItemsSize());
    TEST_ASSERT_EQUAL_STRING("Test Item", menu.GetMenuItemAt(0).GetName().c_str());
}

void test_menu_add_multiple_items() {
    Menu menu;
    menu.AddMenuItem(MenuItem("Item 1"));
    menu.AddMenuItem(MenuItem("Item 2"));
    menu.AddMenuItem(MenuItem("Item 3"));
    
    TEST_ASSERT_EQUAL(3, menu.GetMenuItemsSize());
    TEST_ASSERT_EQUAL_STRING("Item 1", menu.GetMenuItemAt(0).GetName().c_str());
    TEST_ASSERT_EQUAL_STRING("Item 2", menu.GetMenuItemAt(1).GetName().c_str());
    TEST_ASSERT_EQUAL_STRING("Item 3", menu.GetMenuItemAt(2).GetName().c_str());
}

void test_menu_select_next_empty() {
    Menu menu;
    
    menu.SelectNextItem();
    
    TEST_ASSERT_EQUAL(0, menu.GetCurrentIndex());
}

void test_menu_select_next_single_item() {
    Menu menu;
    menu.AddMenuItem(MenuItem("Only Item"));
    
    menu.SelectNextItem();
    
    TEST_ASSERT_EQUAL(0, menu.GetCurrentIndex());
}

void test_menu_select_next_multiple_items() {
    Menu menu;
    menu.AddMenuItem(MenuItem("Item 1"));
    menu.AddMenuItem(MenuItem("Item 2"));
    menu.AddMenuItem(MenuItem("Item 3"));
    
    TEST_ASSERT_EQUAL(0, menu.GetCurrentIndex());
    
    menu.SelectNextItem();
    TEST_ASSERT_EQUAL(1, menu.GetCurrentIndex());
    
    menu.SelectNextItem();
    TEST_ASSERT_EQUAL(2, menu.GetCurrentIndex());
    
    // Should not go past the end
    menu.SelectNextItem();
    TEST_ASSERT_EQUAL(2, menu.GetCurrentIndex());
}

void test_menu_select_previous_at_start() {
    Menu menu;
    menu.AddMenuItem(MenuItem("Item 1"));
    menu.AddMenuItem(MenuItem("Item 2"));
    
    menu.SelectPreviousItem();
    
    TEST_ASSERT_EQUAL(0, menu.GetCurrentIndex());
}

void test_menu_select_previous() {
    Menu menu;
    menu.AddMenuItem(MenuItem("Item 1"));
    menu.AddMenuItem(MenuItem("Item 2"));
    menu.AddMenuItem(MenuItem("Item 3"));
    
    // Move to the end
    menu.SelectNextItem();
    menu.SelectNextItem();
    TEST_ASSERT_EQUAL(2, menu.GetCurrentIndex());
    
    menu.SelectPreviousItem();
    TEST_ASSERT_EQUAL(1, menu.GetCurrentIndex());
    
    menu.SelectPreviousItem();
    TEST_ASSERT_EQUAL(0, menu.GetCurrentIndex());
    
    // Should not go below 0
    menu.SelectPreviousItem();
    TEST_ASSERT_EQUAL(0, menu.GetCurrentIndex());
}

void test_menu_get_selected_item() {
    Menu menu;
    menu.AddMenuItem(MenuItem("Item 1"));
    menu.AddMenuItem(MenuItem("Item 2"));
    
    TEST_ASSERT_EQUAL_STRING("Item 1", menu.GetSelectedItem().GetName().c_str());
    
    menu.SelectNextItem();
    TEST_ASSERT_EQUAL_STRING("Item 2", menu.GetSelectedItem().GetName().c_str());
}

void test_menu_get_selected_item_empty() {
    Menu menu;
    
    // Should return empty item
    TEST_ASSERT_EQUAL_STRING("[Empty menu item]", menu.GetSelectedItem().GetName().c_str());
}

void test_menu_get_item_at_invalid_index() {
    Menu menu;
    menu.AddMenuItem(MenuItem("Item 1"));
    
    // Negative index
    TEST_ASSERT_EQUAL_STRING("[Empty menu item]", menu.GetMenuItemAt(-1).GetName().c_str());
    
    // Out of bounds
    TEST_ASSERT_EQUAL_STRING("[Empty menu item]", menu.GetMenuItemAt(5).GetName().c_str());
}

void test_menu_back_resets_selection() {
    auto parentMenu = std::make_shared<Menu>();
    Menu childMenu(parentMenu);
    
    childMenu.AddMenuItem(MenuItem("Item 1"));
    childMenu.AddMenuItem(MenuItem("Item 2"));
    childMenu.SelectNextItem();
    
    TEST_ASSERT_EQUAL(1, childMenu.GetCurrentIndex());
    
    auto returnedParent = childMenu.Back();
    
    TEST_ASSERT_EQUAL(0, childMenu.GetCurrentIndex());
    TEST_ASSERT_EQUAL(parentMenu.get(), returnedParent.get());
}

void test_menu_display_type() {
    Menu menu(nullptr, DisplayMenu::MAIN_MENU);
    
    TEST_ASSERT_EQUAL(DisplayMenu::MAIN_MENU, menu.GetDisplayMenu());
    
    menu.SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    TEST_ASSERT_EQUAL(DisplayMenu::FUNCTIONAL_MENU, menu.GetDisplayMenu());
}

void test_menu_set_items() {
    Menu menu;
    std::vector<MenuItem> items = {
        MenuItem("A"),
        MenuItem("B"),
        MenuItem("C")
    };
    
    menu.SetMenuItems(items);
    
    TEST_ASSERT_EQUAL(3, menu.GetMenuItemsSize());
    TEST_ASSERT_EQUAL_STRING("A", menu.GetMenuItemAt(0).GetName().c_str());
}

// ============ MenuItem Tests ============

void test_menuitem_default_constructor() {
    MenuItem item;
    
    TEST_ASSERT_EQUAL_STRING("[Empty menu item]", item.GetName().c_str());
    TEST_ASSERT_NULL(item.GetMenu().get());
}

void test_menuitem_with_name() {
    MenuItem item("My Item");
    
    TEST_ASSERT_EQUAL_STRING("My Item", item.GetName().c_str());
}

void test_menuitem_execute_action() {
    bool actionCalled = false;
    MenuItem item("Action Item", [&actionCalled]() {
        actionCalled = true;
    });
    
    TEST_ASSERT_FALSE(actionCalled);
    item.Execute();
    TEST_ASSERT_TRUE(actionCalled);
}

void test_menuitem_execute_null_action() {
    MenuItem item("No Action");
    
    // Should not crash
    item.Execute();
}

void test_menuitem_with_submenu() {
    auto subMenu = std::make_shared<Menu>();
    MenuItem item("SubMenu Item", nullptr, subMenu);
    
    TEST_ASSERT_EQUAL(subMenu.get(), item.GetMenu().get());
}

void test_menuitem_set_action() {
    bool called = false;
    MenuItem item("Item");
    
    item.SetAction([&called]() { called = true; });
    item.Execute();
    
    TEST_ASSERT_TRUE(called);
}

void test_menuitem_set_submenu() {
    MenuItem item("Item");
    auto subMenu = std::make_shared<Menu>();
    
    TEST_ASSERT_NULL(item.GetMenu().get());
    
    item.SetSubMenu(subMenu);
    
    TEST_ASSERT_EQUAL(subMenu.get(), item.GetMenu().get());
}

// ============ Integration: Menu with SubMenu ============

void test_menu_execute_returns_submenu() {
    auto subMenu = std::make_shared<Menu>();
    subMenu->AddMenuItem(MenuItem("SubItem"));
    
    Menu mainMenu;
    mainMenu.AddMenuItem(MenuItem("Go to Sub", nullptr, subMenu));
    
    auto result = mainMenu.ExecuteMenu();
    
    TEST_ASSERT_EQUAL(subMenu.get(), result.get());
}

void test_menu_execute_empty_returns_null() {
    Menu menu;
    
    auto result = menu.ExecuteMenu();
    
    TEST_ASSERT_NULL(result.get());
}

void test_menu_hierarchy_navigation() {
    // Create hierarchy: MainMenu -> SubMenu -> Action
    auto mainMenu = std::make_shared<Menu>(nullptr, DisplayMenu::MAIN_MENU);
    auto subMenu = std::make_shared<Menu>(mainMenu, DisplayMenu::SUB_MENU);
    
    bool actionExecuted = false;
    subMenu->AddMenuItem(MenuItem("Action", [&actionExecuted]() {
        actionExecuted = true;
    }));
    
    mainMenu->AddMenuItem(MenuItem("Open SubMenu", nullptr, subMenu));
    
    // Navigate to submenu
    auto currentMenu = mainMenu->ExecuteMenu();
    TEST_ASSERT_EQUAL(subMenu.get(), currentMenu.get());
    
    // Execute action in submenu
    currentMenu->ExecuteMenu();
    TEST_ASSERT_TRUE(actionExecuted);
    
    // Go back to main
    auto returnedMenu = currentMenu->Back();
    TEST_ASSERT_EQUAL(mainMenu.get(), returnedMenu.get());
}

// ============ Test Runner ============

void setUp(void) {
    // Called before each test
}

void tearDown(void) {
    // Called after each test
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    // Menu basic tests
    RUN_TEST(test_menu_initial_state);
    RUN_TEST(test_menu_add_item);
    RUN_TEST(test_menu_add_multiple_items);
    
    // Menu navigation tests
    RUN_TEST(test_menu_select_next_empty);
    RUN_TEST(test_menu_select_next_single_item);
    RUN_TEST(test_menu_select_next_multiple_items);
    RUN_TEST(test_menu_select_previous_at_start);
    RUN_TEST(test_menu_select_previous);
    
    // Menu item access tests
    RUN_TEST(test_menu_get_selected_item);
    RUN_TEST(test_menu_get_selected_item_empty);
    RUN_TEST(test_menu_get_item_at_invalid_index);
    
    // Menu hierarchy tests
    RUN_TEST(test_menu_back_resets_selection);
    RUN_TEST(test_menu_display_type);
    RUN_TEST(test_menu_set_items);
    
    // MenuItem tests
    RUN_TEST(test_menuitem_default_constructor);
    RUN_TEST(test_menuitem_with_name);
    RUN_TEST(test_menuitem_execute_action);
    RUN_TEST(test_menuitem_execute_null_action);
    RUN_TEST(test_menuitem_with_submenu);
    RUN_TEST(test_menuitem_set_action);
    RUN_TEST(test_menuitem_set_submenu);
    
    // Integration tests
    RUN_TEST(test_menu_execute_returns_submenu);
    RUN_TEST(test_menu_execute_empty_returns_null);
    RUN_TEST(test_menu_hierarchy_navigation);
    
    return UNITY_END();
}
