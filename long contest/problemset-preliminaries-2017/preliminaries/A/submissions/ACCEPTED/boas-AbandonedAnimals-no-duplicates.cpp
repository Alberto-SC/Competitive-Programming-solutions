// EXPECTED RESULT: CORRECT
//

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

int main() {
    
    int shops;
    int total_inventory;

    cin >> shops;
    cin >> total_inventory;

    vector<set<string>> shop_items(shops, set<string>());



    for(int i=0; i<total_inventory; i++) {
        int shop;
        string name;
        cin >> shop >> name;

        shop_items[shop].insert(name);
    }

    int total_items;
    cin >> total_items;

    vector<string> items;

    for(int i=0; i<total_items; i++) {
        string item;
        cin >> item;
        items.push_back(item);
    }

    int cur_shop = 0;
    int cur_item_pos = 0;
    bool ambiguous = false;
    while(true) {

        if (cur_shop >= shops) {
            break;
        }

        if (cur_item_pos >= total_items) {
            while(cur_shop < shops) {
                string cur_item = items[cur_item_pos-1];
                if(shop_items[cur_shop].find(cur_item) != shop_items[cur_shop].end()) {
                    ambiguous = true;
                }
                cur_shop++;
            }

            break;
        }

        string cur_item = items[cur_item_pos];
        string prev_item = cur_item_pos == 0 ? "" : items[cur_item_pos - 1];

        if (shop_items[cur_shop].find(prev_item) != shop_items[cur_shop].end()) {
            ambiguous = true;
        }

        if (shop_items[cur_shop].find(cur_item) != shop_items[cur_shop].end()) {
            
            shop_items[cur_shop].erase(cur_item);


            // go to next letter
            cur_item_pos++;
        } else {
            cur_shop++;
        }

    }


    if (cur_item_pos == total_items) {
        if (ambiguous) {
            cout << "ambiguous" << endl;
        } else {
            cout << "unique" << endl;
        }
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
