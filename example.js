const { BigSet } = require("./build/Release/bigset");

const mySet = new BigSet(); // 创建一个新的 BigSet 实例  Creates a new BigSet instance
mySet.add("value1");
mySet.add("value11");
console.log(mySet.has("value1")); // 应该返回 true   Returns true
mySet.delete("value1");
console.log(mySet.has("value1")); // 应该返回 false   Returns false
console.log(mySet.toString()); // 打印集合内容 "value11"   Prints the set content "value11"

const anotherSet = new BigSet();
anotherSet.add("value2");
console.log(`mySet: ${mySet.toString()}`);
console.log(`anotherSet: ${anotherSet.toString()}`);
