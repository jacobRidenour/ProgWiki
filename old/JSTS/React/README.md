# Background information

Web page is loaded; browser takes the HTML code and creates tree-like structure: Document Object Model (DOM)

- We can change page content in response to user actions with JavaScript by querying and updating DOM elements
- This becomes unwieldy with more complicated sites
- React uses small, reusable components to efficiently create & update DOM elements
  - Different sections could be examples of separate components (sidebar, navigation bar, main view)
  - React application is a tree of components with the app as the root

# Prerequisites

- [Node.js](https://nodejs.org/en/download)

# VS Code Setup

Extensions:

- Prettier - Code Format
  - Settings (Ctrl+,): format on save (Yes)
- ES7+ - useful shortcuts for React
  - rafce -> React Arrow Function Component Export

Shortcuts/useful commands:

- Emmet: wrap with abbreviation (for e.g. quickly adding <Fragment />)
- Ctrl+D - repeat N times to select the next N iterations of a variable and change them all at once; escape to exit

# React Developer Tools

- Useful for seeing how things work/debugging. Get it for [Firefox](https://addons.mozilla.org/en-US/firefox/addon/react-devtools/) or [Chrome](https://chrome.google.com/webstore/detail/react-developer-tools/fmkadmapgofadopljbjfkapdkoienihi) (may be buggy in Firefox?)

# Application Setup

1. Set up Vite: `npm create vite@latest`
2. Bootstrap - for modern UI look - `npm install bootstrap`

# File/Folder Structure

- node_modules - third party libraries like React and other tools - should never have to touch this
- public - where public assets (images videos etc) are
- src - source code; default has 1 component, the App component
- index.html - very basic HTML template; has root div - container for application; script representing entry point for app
- package.json - information about the project; name, dependencies, development dependencies (not deployed)
- tsconfig.json - most often won't need to touch this
- vite.config.ts - most often won't need to touch this

# Create a component

- Add file to src folder; traditionally `.tsx` for React components, `.ts` for plain TypeScript files
- Components are usually a class or function; functions more common
- Components are traditionally in the `/components` folder

# Prop(ertie)s vs. States

| Props                       | States                      |
| :-------------------------- | :-------------------------- |
| Input passed to a component | Data managed by a component |
| Similar to function args    | Similar to local variables  |
| (Treat as) Immutable        | Mutable                     |

For both props & states, changes will cause a re-render
