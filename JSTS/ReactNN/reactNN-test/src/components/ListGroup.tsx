import { Fragment } from "react";
//import { MouseEvent } from "react";
import { useState } from "react";

// pass in the items for the list, and a string for the heading
interface ListGroupProps {
  items: string[];
  heading: string;
  // function that takes string (item)- the selected item; returns void
  // like onClick
  onSelectItem: (item: string) => void;
}

function ListGroup({ items, heading, onSelectItem }: ListGroupProps) {
  // add a hook - a way to tap into built-in features of react; useState is just one example of a hook
  // arr[0] = variable (selectedIndex)
  // arr[1] = updater function
  const [selectedIndex, setSelectedIndex] = useState(-1);

  //items = [];

  //const emptyListError = items.length === 0 ? <p>No item found.</p> : null;

  const emptyListErrorFunction = () => {
    return items.length === 0 ? <p>No item found.</p> : null;
  };

  // handler
  //const handleClick = (event: MouseEvent) => console.log(event);

  return (
    // want to add a header, but a component cannot return more than 1 element
    // in React, so...
    <Fragment>
      <h1>{heading}</h1>

      {emptyListErrorFunction()}
      <ul className="list-group">
        {items.map((item, index) => (
          <li
            className={
              selectedIndex === index
                ? "list-group-item active"
                : "list-group-item"
            }
            key={item}
            onClick={() => {
              setSelectedIndex(index);
              onSelectItem(item);
            }}
            //{console.log("Clicked " + item + " at index " + index)}
          >
            {item}
          </li> // irl, the key should be a unique property like an ID for dynamically updated content
        ))}
      </ul>
    </Fragment>
  );
}

export default ListGroup;
