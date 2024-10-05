const bigset = require("./build/Release/bigset");

// 使用 BigSet 的方法
bigset.add("Hello");
bigset.add("World");
console.log(bigset.toString()); // 输出: "Hello, World, "
console.log(bigset.getLength()); // 输出: 2
console.log(bigset.has("Hello")); // 输出: true
console.log(bigset.has("Bye")); // 输出: false

bigset.delete("Hello");
console.log(bigset.has("Hello")); // 输出: false
console.log(bigset.getLength()); // 输出: 1
console.log(bigset.toString()); // 输出: "World, "

console.time();
for (let i = 0; i <= 1000_0000; i++) {
    bigset.add(i.toString());
    if (i % 10_0000 == 0) {
        console.log(`已添加 ${i} 个元素`);
        console.timeLog();
    }
}
console.log(bigset.has("999999"));
bigset.delete("999999");
console.log(bigset.has("999999"));