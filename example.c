#include"json_util.h"
#include<stdio.h>
/*

Example taken from https://opensource.adobe.com/Spry/samples/data_region/JSONDataSetSample.html#Example3
 
{
	"id": "0001",
	"type": "donut",
	"name": "Cake",
	"ppu": 0.55,
	"batters":
		{
			"batter":
				[
					{ "id": "1001", "type": "Regular" },
					{ "id": "1002", "type": "Chocolate" },
					{ "id": "1003", "type": "Blueberry" },
					{ "id": "1004", "type": "Devil's Food" }
				]
		},
	"topping":
		[
			{ "id": "5001", "type": "None" },
			{ "id": "5002", "type": "Glazed" },
			{ "id": "5005", "type": "Sugar" },
			{ "id": "5007", "type": "Powdered Sugar" },
			{ "id": "5006", "type": "Chocolate with Sprinkles" },
			{ "id": "5003", "type": "Chocolate" },
			{ "id": "5004", "type": "Maple" }
		]
}

*/

int main(void)
{

    FILE* fp;
    fp = fopen ("example.json", "w+");

    // batter
    int batter_qty = 4;
    char* batter_ids[] = {"1001","1002","1003","1004"};
    char* batter_types[] = {"Regular", "Chocolate", "Blueberry", "Devil's Food"};

    char **batter_group = (char **)malloc(sizeof(char*)*batter_qty);

    for(int i=0; i<batter_qty ;i++)
    {
        char *item_id = j_item("id", batter_ids[i]);
        char *item_type = j_item("type", batter_types[i]);

        char *batter = j_group("",
                            make_group(2,
                                    item_id,
                                    item_type
                            ),
                            2,
                            "{}"
        );
        batter_group[i] = batter;
    }

    char *batter_array = j_group("batters",batter_group,batter_qty,"[]");

    // toppings
    int topping_qty = 7;
    char* topping_ids[] = {"5001","5002","5005","5007", "5006","5003","5004"};
    char* topping_types[] = {"None", "Glazed", "Sugar", "Powdered Sugar", "Chocolate with Sprinkles", "Chocolate", "maple"};

    char **topping_group = (char **)malloc(sizeof(char*)*topping_qty);

    for(int i=0; i<topping_qty;i++)
    {
        char *item_id = j_item("id", topping_ids[i]);
        char *item_type = j_item("type", topping_types[i]);

        char *topping = j_group("",
                            make_group(2,
                                    item_id,
                                    item_type
                            ),
                            2,
                            "{}"
        );
        topping_group[i] = topping;
    }

    char *topping_array = j_group("topping",topping_group,topping_qty,"[]");

    //fprintf(fp, "%s\n",batter_array);
    //fprintf(fp, "%s\n",topping_array);

    char *output = j_group("",
                    make_group(6,
                        j_item("id","0001"),
                        j_item("type","donut"),
                        j_item("name","cake"),
                        j_item("ppu","0.55"),
                        j_group("batters",make_group(1,batter_array),1,"{}"),
                        topping_array
                    ),
                    6,
                    "{}"
    );

    fprintf(fp, "%s\n",output);

    fclose(fp);

    return 0;
}
