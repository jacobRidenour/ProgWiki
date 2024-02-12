const express = require('express');
const { exec } = require('child_process');
const app = express();
const port = 3001;

app.get('/execute-python-script', (req, res) => {
  exec('python model-loader/model_loader.py', (error, stdout, stderr) => {
    if (error) {
      console.error(`Error executing Python script: ${error}`);
      res.status(500).send('Error loading model');
      return;
    }

    console.log(`Python script output: ${stdout}`);
    res.send('Model loaded successfully');
  });
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});