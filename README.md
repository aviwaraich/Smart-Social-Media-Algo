# Smart-Social-Media-Algo

Graffit - Smart Social Media 

Since we’re all socially distanced, it is even more important that we connect with one another through online platforms. Social media platforms like Facebook, Twitter, Snapchat, etc. all offer ways for you to connect with others. In the simple case, they allow us to connect with other human users, with brands, and with communities. These topics are connected into an intricate web of social connections, a social network! This Project is about making a smart social networks algorithm called Graffit.

In Graffit, we have users (like you ;) and me) and brands (like UTSC). 
Users have a list of friends and brands they follow. Brandshave a list of similar brands. Graffit will be manipulating a network with these kinds of structures, so users can find more firends.

**For Users, We have:**
- create_user(char[] name)
    - Each name will be unique.
- delete_user(User user)
- add_friend(User user, User friend)
    - Friends here are a two-way connection. If you’re my friend, I have to be your friend, alphabetically.
- remove_friend(User user, User friend)
- follow_brand(User user, Brand brand)
    - Alphabetically.
- unfollow_brand(User user, Brand brand)
- print_user_data(User user)
    - Prints out: the user‘s name, the user’s list of friends, and a list of brands they follow. See the assignment for the exact print functions to be used.
- get_degrees_of_connection(User a, User b) 
    - Distance between two users.

**For Brands, We have:**
- populate_brand_matrix(char[] file_name)
  - Turn an adjacency matrix represented in a txt file into a network of brands. This txt file will be formatted in a specific way:
    - The first row will be brand names. Each brand name will be unique and will be separated by one space character.
    - The following rows will create a NxN matrix. This will be a valid adjacency matrix, so the element at (x, y) = the element at (y,x). The values will be either 0 or 1 and will be separated by one space character.
- connect_similar_brands(Brand a, Brand b)
  - Some brands are very alike, so have a database to maintain a record of similar brands.
- remove_similar_brands(Brand a, Brand b)
- print_brand_data(Brand brand)
  - Prints out: the brand name and a list of similar brands. See the assignment for the exact print functions to be used.
  

Many social media companies have a “suggested friends” feature. I have a buildin function to get a smart suggested friend. 
Returns the not-already-friended user with the most brands they follow in common. If there’s a tie, returns the user with the most friends in common. 
If there’s still a tie, returns reverse-alphabetically.

**get_suggested_friend(User user)**
- Graffit is a company of the future, and “suggested friends” is a feature of the past. To stay ahead of competitors, Graffit pioneered the “add N suggested friends” feature. It also implemented the “follow N suggested brands” feature. (If there are less than N options to suggest, suggest as many as possible.) 
- These will be implemented through the following functions:
    - add_suggested_friends(User u, int n)
        - Same rules as the get_suggested_friend(...) function.
    - follow_suggested_brands(User u, int n)
        - A suggested brand is the brand with the most similarities with brands the user already follows. If there’s a tie, the suggested brand is the one that comes first reverse-alphabetically.
