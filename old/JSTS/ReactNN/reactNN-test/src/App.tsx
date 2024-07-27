import ListGroup from "./components/ListGroup";
import Alert from "./components/Alert";
import Button from "./components/Button";
import Message from "./Message";
import { useState } from "react";

function App() {
  let items = [
    "New York",
    "San Francisco",
    "Tokyo",
    "London",
    "Atlanta",
    "Minneapolis",
  ];

  // handler
  const handleSelectItem = (item: string) => {
    console.log(item);
  };

  // state variable for showing Alert only when button is clicked
  const [alertVisible, setAlertVisibility] = useState(false);

  return (
    // <div>
    //   <h1>Testing Model Loader</h1>
    //   <Message />
    // </div>
    <div>
      <ListGroup
        items={items}
        heading="Cities"
        onSelectItem={handleSelectItem}
      />
      {alertVisible && (
        <Alert onClose={() => setAlertVisibility(false)}>
          Thanks <span>for clicking :) </span>
        </Alert>
      )}
      <Button color="secondary" onClick={() => setAlertVisibility(true)}>
        Click Me!
      </Button>
      <Message />
    </div>
  );
}

export default App;

// Currently our DOM looks like a tree:
//
/*
   App
    |
   Child

   When React application strats, React takes this component tree and creates a virtual DOM (JavaScript data structure)
    // lightweight, in-memory representation of our tree where each node represents a component and its properties
    // when the state/data of a component changes, React updates the corresponding node in the vDOM, comparing current with previous version
    // to determine which nodes need updated; React itself does not update the DOM, it's done by react-dom

    // React is a platform-agnostic library pretty much only good for building user interfaces
    // A full app will likely need a framework to implement different concerns:
      // routing, HTTP calls, managing app state, internationalization, form validation, animations, etc.
    // React doesn't care what additional tools we're using

*/
