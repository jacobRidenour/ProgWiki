# SeniorCapstone_Team8

Senior Capstone project Team 8 AY 2023-24

# Dependencies

- [Node.js](https://nodejs.org/en/download)

# How it was set up, file structure

The project was created with the following commands:

```
npx create-react-app stego-site
cd stego-site
```

Those commands created our basic project structure:

- `src/` - where React (front-end) code is written
- `public/` - HTML template, static assets (images, icons, etc.)
- `package.json` - lists project dependencies, configuration
- `package-lock.json` - to lock down versions of installed packages
- `README.md` - you're lookin' at it.

Additional directories:

- `server/` - where Node.js (back-end) code is written
- `python/` - where Python scripts are stored

# Development & Testing

If testing locally:

`PORT=#### npm start`

Recommend not using the default port, as the implementation currently uses a node.js server running on the default port (3000).

If ready to test deployment:

`npm run build`
