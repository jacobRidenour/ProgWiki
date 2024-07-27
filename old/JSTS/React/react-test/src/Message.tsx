function Message() {
    const name = 'Jacob';
    
    // JSX: JavaScript XML
    // babel.js.io/repl - see how this code gets converted to JavaScript
    if (name) {
        return <h1>Hello {name}</h1>;
    }
    return <h1>Hello world</h1>;
    // anything in {} can be a variable or expression that returns a value
}

// export as the default object for this module
export default Message;