# Assignment 11

## Roll no. `31311`

```js
> use db
switched to db db
> db.createCollection("items")
{ "ok" : 1 }
> db.items.insertMany([
...     { name: 'Banana', category: 'Fruits', price: 0.99, quantity: 120 },
...     { name: 'Milk', category: 'Dairy', price: 2.49, quantity: 50 },
...     { name: 'Carrot', category: 'Vegetables', price: 0.69, quantity: 200 },
...     { name: 'Bread', category: 'Bakery', price: 1.99, quantity: 75 },
...     { name: 'Apple', category: 'Fruits', price: 1.29, quantity: 150 },
...     { name: 'Eggs', category: 'Dairy', price: 3.19, quantity: 60 },
...     { name: 'Orange', category: 'Fruits', price: 0.89, quantity: 100 },
...     { name: 'Cheese', category: 'Dairy', price: 4.99, quantity: 40 },
...     { name: 'Potato', category: 'Vegetables', price: 0.49, quantity: 250 },
...     { name: 'Yogurt', category: 'Dairy', price: 1.79, quantity: 80 },
...     { name: 'Tomato', category: 'Vegetables', price: 0.99, quantity: 180 },
...     { name: 'Chicken Breast', category: 'Meat', price: 5.99, quantity: 30 },
...     { name: 'Salmon', category: 'Fish', price: 10.99, quantity: 20 },
...     { name: 'Pasta', category: 'Grains', price: 2.29, quantity: 90 },
...     { name: 'Rice', category: 'Grains', price: 1.49, quantity: 200 },
...     { name: 'Sugar', category: 'Baking', price: 1.19, quantity: 150 },
...     { name: 'Flour', category: 'Baking', price: 0.89, quantity: 140 },
...     { name: 'Olive Oil', category: 'Condiments', price: 6.49, quantity: 50 },
...     { name: 'Salt', category: 'Condiments', price: 0.99, quantity: 100 },
...     { name: 'Black Pepper', category: 'Condiments', price: 2.99, quantity: 60 },
...     { name: 'Ice Cream', category: 'Frozen', price: 4.49, quantity: 30 }
... ])
{
        "acknowledged" : true,
        "insertedIds" : [
                ObjectId("66fe23cde6a16c259b74c4de"),
                ObjectId("66fe23cde6a16c259b74c4df"),
                ObjectId("66fe23cde6a16c259b74c4e0"),
                ObjectId("66fe23cde6a16c259b74c4e1"),
                ObjectId("66fe23cde6a16c259b74c4e2"),
                ObjectId("66fe23cde6a16c259b74c4e3"),
                ObjectId("66fe23cde6a16c259b74c4e4"),
                ObjectId("66fe23cde6a16c259b74c4e5"),
                ObjectId("66fe23cde6a16c259b74c4e6"),
                ObjectId("66fe23cde6a16c259b74c4e7"),
                ObjectId("66fe23cde6a16c259b74c4e8"),
                ObjectId("66fe23cde6a16c259b74c4e9"),
                ObjectId("66fe23cde6a16c259b74c4ea"),
                ObjectId("66fe23cde6a16c259b74c4eb"),
                ObjectId("66fe23cde6a16c259b74c4ec"),
                ObjectId("66fe23cde6a16c259b74c4ed"),
                ObjectId("66fe23cde6a16c259b74c4ee"),
                ObjectId("66fe23cde6a16c259b74c4ef"),
                ObjectId("66fe23cde6a16c259b74c4f0"),
                ObjectId("66fe23cde6a16c259b74c4f1"),
                ObjectId("66fe23cde6a16c259b74c4f2")
        ]
}
```
## Calculate the total quantity of all items in the inventory.

```js 
> db.items.mapReduce(
...     function(){emit(null, this.quantity);},
...     function(key, values){return Array.sum(values)},
...     {
...         out:"total_items_sold"
...     }
... )
{ "result" : "total_items_sold", "ok" : 1 }

> db.total_items_sold.find()
{ "_id" : null, "value" : 2175 }
```
## Determine the average price of items in each category.

```js
> db.items.mapReduce(
...     function(){emit(this.category, this.price);},
...     function(key,values){return [key, Array.avg(values)];},
...     {
...         out:"category_avg_price"
...     }
... )
{ "result" : "category_avg_price", "ok" : 1 }

> db.category_avg_price.find().pretty()
{ "_id" : "Meat", "value" : [ "Meat", 5.99 ] }
{ "_id" : "Condiments", "value" : [ "Condiments", 3.49 ] }
{ "_id" : "Dairy", "value" : [ "Dairy", 3.115 ] }
{ "_id" : "Fish", "value" : [ "Fish", 10.99 ] }
{ "_id" : "Baking", "value" : [ "Baking", 1.04 ] }
{ "_id" : "Fruits", "value" : [ "Fruits", 1.0566666666666666 ] }
{ "_id" : "Vegetables", "value" : [ "Vegetables", 0.7233333333333333 ] }
{ "_id" : "Grains", "value" : [ "Grains", 1.8900000000000001 ] }
{ "_id" : "Bakery", "value" : [ "Bakery", 1.99 ] }
{ "_id" : "Frozen", "value" : [ "Frozen", 4.49 ] }

```
## Count the number of items in each category.

```js

> db.items.mapReduce(
...     function(){emit(this.category, this.quantity)},
...     function(key,values){return {key : Array.sum(values)};},
...     {
...         out:"category_no_items"
...     }
... )
{ "result" : "category_no_items", "ok" : 1 }
> db.category_no_items.find().pretty()
{ "_id" : "Vegetables", "value" : { "key" : 630 } }
{ "_id" : "Fruits", "value" : { "key" : 370 } }
{ "_id" : "Fish", "value" : { "key" : 20 } }
{ "_id" : "Frozen", "value" : { "key" : 30 } }
{ "_id" : "Bakery", "value" : { "key" : 75 } }
{ "_id" : "Grains", "value" : { "key" : 290 } }
{ "_id" : "Condiments", "value" : { "key" : 210 } }
{ "_id" : "Meat", "value" : { "key" : 30 } }
{ "_id" : "Baking", "value" : { "key" : 290 } }
{ "_id" : "Dairy", "value" : { "key" : 230 } }
> 
```

## Find the maximum price of items in the store.

```js
db.items.mapReduce(
    
)
```

## Calculate the total revenue generated from all items (price * quantity).

## Find the item with the highest quantity in stock.

## List the total number of unique items across all categories.

## Count how many items have a price greater than $2.00.

## Group items by supplier (if added) and calculate total stock for each supplier.

## Calculate the total number of items below a certain price threshold (e.g., $1.00).