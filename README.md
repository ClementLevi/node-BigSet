# BigSet

一个高性能的集合类，用于处理大量元素的添加、查找和删除操作。

[ENGLISH](./README.en.md) | 中文

## 特性

- 支持高效的元素添加和查找
- 自动维护元素的唯一性
- 能够处理百万级别的数据
- 由N-API打造CPP插件而成
- 目前仅支持字符串
- **CommonJS**支持
- ~整个项目都是AI生成的，我根本看不懂里面写了什么~

## 安装

使用 npm 安装：

```bash
npm install @clement_levi/bigset
```

## 使用示例

以下是如何使用 BigSet 的示例：

```javascript
const BigSet = require('bigset');

// 创建一个 BigSet 实例
const myBigSet = new BigSet();

// 添加元素
myBigSet.add("Hello");
myBigSet.add("World");

// 暂不支持字符串以外的元素
// 如果您想添加对象等元素，请善用'JSON.stringify()'或'*.toString()'方法将其转换为字符串
myBigSet.add(1); // TypeError: A string was expected


console.log(myBigSet.toString()); // 输出: "Hello, World, "
console.log(myBigSet.getLength()); // 输出: 2
console.log(myBigSet.has("Hello")); // 输出: true
console.log(myBigSet.has("Bye")); // 输出: false

// 删除元素
myBigSet.delete("Hello");
console.log(myBigSet.has("Hello")); // 输出: false
console.log(myBigSet.toString()); // 输出: "World, "
```

## 测试

通过 Mocha 运行测试：

```bash
npm run test
```

## 贡献

欢迎任何形式的贡献！如果您有想法，请创建Issue或提交 Pull Request。

1. Fork 此仓库
2. 创建您的特性分支 (git checkout -b feature/YourFeature)
3. 提交您的更改 (git commit -m 'Add some feature')
4. 推送到分支 (git push origin feature/YourFeature)
5. 创建新的 Pull Request

## 许可

该项目采用 MIT 许可，详情请查看 [LICENSE](./LICENSE) 文件。

## 免责声明

本项目基于 C++ 插件开发，并在 Node.js 环境中运行。请确保在使用前按照说明正确构建和配置插件。

开发过程中广泛使用了[Fitten Code](https://code.fittentech.com/)。
