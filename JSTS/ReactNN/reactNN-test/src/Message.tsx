import { useEffect, useState } from "react";
import { exec, ExecException } from "child_process";

function Message() {
  const [message, setMessage] = useState<string>("");

  useEffect(() => {
    // Execute the Python script when the component mounts
    console.log("Effect triggered");
    exec(
      "python model-loader/model_loader.py",
      (error: ExecException | null, stdout: string, stderr: string) => {
        if (error !== null) {
          console.error(`Error executing Python script: ${error}`);
          setMessage("Error loading model");
          return;
        }

        console.log(`Python script output: ${stdout}`);
        setMessage("Model loaded successfully");
      }
    );
  }, []);

  return <div>{message}</div>;
}

// export as the default object for this module
export default Message;
