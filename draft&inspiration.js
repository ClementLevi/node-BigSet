// @ts-nocheck
// This is a draft and inspiration code for a BigSet class that can store a large number of values efficiently.
// 这是一个 BigSet 类的草稿和启发代码，本打算有效地存储大量值。
// It works not fine, so I made the CPP version.
// 这段代码跑得不好，所以我写了个 CPP 版本。
const { createHash } = require("node:crypto");

class BigSet {
    static SET_CAPACITY = 65535; // A set's maximum capacity / 一个 set 的容量上限
    constructor() {
        // Initialize all sets / 初始化所有 set
        this.sets = [];
        this.sets.push({});
        // Currently, there is only one set with a length of 0 / 当前只有一个 set，其长度为 0
        this.sets_sizes = [0];
        // Currently using the 0th set / 当前使用第 0 个 set
        this.curr_set = 0;
        // Total length / 总长度
        this.length = 0;
    }

    add(value) {
        // Calculate hash value / 计算 hash 值
        const hash = createHash("sha256").update(value).digest("hex");
        // If the current set is full, create a new set / 如果当前 set 已满，则创建一个新的 set
        if (
            Object.keys(this.sets[this.curr_set]).length >= BigSet.SET_CAPACITY
        ) {
            this.curr_set++;
            this.sets.push({});
            this.sets_sizes.push(0);
        }

        // Point the cursor this.curr_set to the current available set / 设置游标 this.curr_set 指向当前有空位的 set
        const currentSet = this.sets[this.curr_set];

        // Add value to the current set / 将 value 添加到当前 set 中
        if (!currentSet[hash]) {
            currentSet[hash] = [];
        }

        // If the array does not exist, create an array and add the value to it / 如果数组不存在，则创建一个数组，并将 value 添加到数组中
        const valuesArray = currentSet[hash];

        // Traverse the array to check if the value exists / 遍历数组查找 value 是否存在
        if (!valuesArray.includes(value)) {
            valuesArray.push(value);
            // Update the current set's length / 更新当前 set 的长度
            this.sets_sizes[this.curr_set]++;
            this.length++;
        }
    }

    has(value) {
        // Calculate the hash value of the value / 计算 value 的 hash 值
        const hash = createHash("sha256").update(value).digest("hex");
        const currentSet = this.sets[this.curr_set];

        // If the array does not exist, the value surely does not exist, return false / 如果数组不存在，则必然不存在 value，返回 false
        if (!currentSet[hash]) {
            return false;
        }

        // If the array exists, traverse the array to check if the value exists / 如果数组存在，则遍历数组，查找 value 是否存在
        const valuesArray = currentSet[hash];
        return valuesArray.includes(value);
    }

    delete(value) {
        // Call this.has(value) to check if the value exists / 调用 this.has(value) 判断 value 是否存在
        if (!this.has(value)) {
            throw new Error(`Value ${value} does not exist.`); // If the value exists, delete it / 如果 value 存在，则删除 value
        }

        // If the value exists, delete the value / 如果 value 存在，则删除 value
        const hash = createHash("sha256").update(value).digest("hex");
        const valuesArray = this.sets[this.curr_set][hash];

        // Delete the value and update the current set's length / 删除 value 并更新当前 set 的长度
        const index = valuesArray.indexOf(value);
        if (index !== -1) {
            valuesArray.splice(index, 1);
            this.sets_sizes[this.curr_set]--;
            this.length--;
        }
    }

    random() {
        // Randomly select a set / 随机选择一个 set
        const randomSetIndex = Math.floor(Math.random() * this.sets.length);
        const randomSet = this.sets[randomSetIndex];

        // Randomly select an element / 随机选择一个元素
        const keys = Object.keys(randomSet);
        const randomKey = keys[Math.floor(Math.random() * keys.length)];
        const randomValuesArray = randomSet[randomKey];

        // Return the random element / 返回随机元素
        const randomValue =
            randomValuesArray[
                Math.floor(Math.random() * randomValuesArray.length)
            ];
        return randomValue;
    }
    toString() {
        return this.sets
            .map((set) => Object.values(set))
            .flat()
            .join(", ");
    }
}

if (require.main === module) {
    console.log(
        `object: "Hi", hash:${createHash("sha256").update("Hi").digest("hex")}`
    );
    const bigSet = new BigSet();
    bigSet.add("Hi");
    bigSet.add("Hello");
    bigSet.add("World");
    bigSet.add("Hi");
    console.log(bigSet.toString());
    console.log(bigSet.has("Hi"));
    console.log(bigSet.has("Bye"));
    console.log(bigSet.random());
    bigSet.delete("Hi");
    console.log(bigSet.has("Hi"));
    console.time("add");
    for (let i = 0; i < 10_0000; i++) {
        bigSet.add(i.toString());
        if (!(i % 1000)) {
            console.timeLog("add");
            console.log(i);
        }
    }
    console.log(bigSet.length);
}
