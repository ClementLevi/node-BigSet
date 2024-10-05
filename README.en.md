# BigSet

A high-performance collection class for handling large-scale element addition, lookup, and deletion operations.

ENGLISH | [中文](./README.md)

## Features

- Supports efficient element addition and lookup
- Automatically maintains the uniqueness of elements
- Capable of handling millions of data
- Built by N-API CPP plugin
- Currently supports strings only
- **CommonJS** style
- ~The entire project is AI generated; I don't bloody understand what's inside at all~

## Installation

Install via npm:

```bash
npm install bigset
```

## Usage Example

Here is an example of how to use BigSet:

```javascript
const BigSet = require('bigset');

// Create an instance of BigSet
const myBigSet = new BigSet();

// Add elements
myBigSet.add("Hello");
myBigSet.add("World");

// Currently does not support elements other than strings
// If you want to add objects or other elements, please use 'JSON.stringify()' or '*.toString()' method to convert them to strings
myBigSet.add(1); // TypeError: A string was expected

console.log(myBigSet.toString()); // Output: "Hello, World, "
console.log(myBigSet.getLength()); // Output: 2
console.log(myBigSet.has("Hello")); // Output: true
console.log(myBigSet.has("Bye")); // Output: false

// Delete an element
myBigSet.delete("Hello");
console.log(myBigSet.has("Hello")); // Output: false
console.log(myBigSet.toString()); // Output: "World, "
```

## Testing

Run tests using Mocha:

```bash
npm run test
```

## Contributing

Any form of contribution is welcome! If you have ideas, please create issues or submit Pull Requests.

1. Fork this repository
2. Create your feature branch (git checkout -b feature/YourFeature)
3. Commit your changes (git commit -m 'Add some feature')
4. Push to the branch (git push origin feature/YourFeature)
5. Create a new Pull Request

## License

This project is licensed under the MIT License. Please check the [LICENSE](./LICENSE) file for details.

## Disclaimer

This project is developed based on C++ plugins and runs in a Node.js environment. Please ensure to correctly build and configure the plugin as per the instructions before use.

[Fitten Code](https://code.fittentech.com/) is widely used during development.
