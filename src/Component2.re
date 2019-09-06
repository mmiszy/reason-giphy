[@react.component]
let make = () => {
  let (show, setShow) = React.useState(() => true);

  <div>
    <button onClick={_event => setShow(show => !show)}> {React.string("Toggle")} </button>
    {show ? React.string("Siema!") : React.null}
  </div>;
};
