open Utils;

[@react.component]
let make = () =>
  <div>
    <h1> {str("ReasonML Modules, by SeaMonster Studios")} </h1>
    <p>
      {str("This is a repo of ReasonML utils and ReasonReact components.")}
    </p>
  </div>;