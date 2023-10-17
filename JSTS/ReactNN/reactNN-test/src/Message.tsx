import { useEffect, useState } from "react";
// import { exec, ExecException } from "child_process";

function Message() {
  const [message, setMessage] = useState("");

  useEffect(() => {
    // Make an HTTP request to the server-side endpoint
    fetch("/execute-python-script")
      .then((response) => response.text())
      .then((data) => {
        // Handle the response here
        console.log("Model loading message:", data);
        setMessage(data);
      })
      .catch((error) => {
        console.error("Error loading model:", error);
        setMessage("Error loading model");
      });
  }, []);

  return <div>{message}</div>;
}

// export as the default object for this module
export default Message;
