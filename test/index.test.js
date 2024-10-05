// test/index.test.js
// 引入必要的模块和依赖
const path = require("path");
const { describe, it, beforeEach } = require("mocha");
const { expect } = require("chai");
const { BigSet } = require("../index.cjs"); // 确保路径指向你的 CommonJS 入口文件

// 对 BigSet 类进行测试
describe("BigSet", function () {
    let bigset; // 声明一个变量用于保存 BigSet 实例

    // 在每个测试之前创建一个新的 BigSet 实例
    beforeEach(function () {
        bigset = new BigSet(); // 创建新的 BigSet 实例
    });

    // 测试添加元素的功能
    it("should add elements correctly", function () {
        bigset.add("Hello");
        bigset.add("World");

        expect(bigset.toString()).to.equal("Hello, World, ");
        expect(bigset.getLength()).to.equal(2);
        expect(bigset.has("Hello")).to.be.true;
        expect(bigset.has("Bye")).to.be.false;
    });

    // 测试删除元素的功能
    it("should delete elements correctly", function () {
        bigset.add("Hello");
        bigset.add("World");

        bigset.delete("Hello");
        expect(bigset.has("Hello")).to.be.false;
        expect(bigset.getLength()).to.equal(1);
        expect(bigset.toString()).to.equal("World, ");
    });

    // 测试查找元素的功能
    it("can find an element", function () {
        bigset.add("Hello");
        bigset.add("World");
        bigset.add("Bye");
        expect(bigset.has("Hello")).to.be.true;
        expect(bigset.has("Bye-bye")).to.be.false;
    });

    // 值不能是非字符串类型
    it("value cannot be type other than string", function () {
        expect(() => bigset.add(123)).to.throw(
            TypeError,
            "A string was expected"
        );
    });

    // 测试处理大量元素的效率
    it("should handle a slightly large number of elements efficiently", function () {
        console.time("Add 1 million elements");
        for (let i = 0; i < 1_000_000; i++) {
            // 1 million
            bigset.add(i.toString());
            if (i % 100000 === 0) {
                console.log(`已添加 ${i} 个元素。\t${i} elements added.`);
            }
        }
        console.timeEnd("Add 1 million elements");

        expect(bigset.has("999999")).to.be.true;
        expect(bigset.has("1")).to.be.true;

        bigset.delete("999999");
        expect(bigset.has("1")).to.be.true;
        expect(bigset.has("999999")).to.be.false;
    });

    it("should handle a super large number of elements efficiently (should fail due for timeout or OOM)", function () {
        console.time("Add 1 million elements");
        for (let i = 0; i < 100_000_000; i++) {
            // 100 million
            bigset.add(i.toString());
            if (i % 100000 === 0) {
                console.log(`已添加 ${i} 个元素。\t${i} elements added.`);
            }
        }
        console.timeEnd("Add 1 million elements");

        expect(bigset.has("9999999")).to.be.true;
        expect(bigset.has("1")).to.be.true;

        bigset.delete("9999999");
        expect(bigset.has("1")).to.be.true;
        expect(bigset.has("9999999")).to.be.false;

        // ! OOM risk
        // ! 注意：如果内存不足，可能会导致程序崩溃
        // ? lol i have 128G memory and it works fine for me.
    });
});
