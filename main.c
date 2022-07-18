#include "graffit.c"

// testing code
int main() { 
    // Users & Brands
    User* angela = create_user("Angela");
    User* brian = create_user("Brian");
    add_friend(angela, brian);
    // Except to see Angela with her friend Brian
    print_user_data(angela); 
    // Expect to see Brian with his friend Angela
    print_user_data(brian); 
    int angela_and_brian = get_degrees_of_connection(angela, brian);
    // Expect 1
    populate_brand_matrix("brands.txt");
    printf("Connections between Angela and Brian: %d\n", angela_and_brian);
    follow_brand(angela, "brandonRufino"); 
    // Angela should now follow brandonRufino
    print_user_data(angela); 
    print_brand_data("brandZero"); // Similar to brandonRufino
    print_brand_data("brandonRufino"); // Similar to brandZero
    print_brand_data("brandTwo"); // Not similar to anything
    connect_similar_brands("brandZero", "brandTwo");
    print_brand_data("brandZero"); // Similar to brandonRufino and brandTwo
    print_brand_data("brandonRufino"); // Similar to brandZero
    print_brand_data("brandTwo"); // Simlar to brandZero

    // Last Part
    User* will = create_user("Will");
    add_friend(angela, will);
    print_user_data(will); // Expect to see Will with his friend Angela
    // This should return Will so
    User* brianSuggested = get_suggested_friend(brian);
    print_user_data(brianSuggested); // We should see Will here again
    User* mustafa = create_user("Mustafa");
    add_friend(angela, mustafa);
    add_suggested_friends(mustafa, 2);
    // Expect to see Mustafa with friends Angela, Brian, and Will
    print_user_data(mustafa);
    follow_brand(will, "brandTwo");
    follow_brand(mustafa, "brandZero"); 
    follow_suggested_brands(mustafa, 1);
    print_user_data(mustafa); // Mustafa should now also follow brandTwo
}
