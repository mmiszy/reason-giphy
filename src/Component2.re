type state = {
  count: int,
  show: bool,
};

type action =
  | Click
  | Toggle;

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Click => {...state, count: state.count + 1}
        | Toggle => {...state, show: !state.show}
        },
      {count: 0, show: true},
    );

  <div>
    <button onClick={_ => dispatch(Toggle)}> {React.string("Toggle")} </button>
    {state.show ? React.string("Siema!") : React.null}
    <button onClick={_ => dispatch(Click)}> {React.string(string_of_int(state.count))} </button>
  </div>;
};
