[@react.component]
let make = () => {
  let (state, setState) = React.useState(() => "");

  let onChange =
    React.useCallback0(e => {
      let value: string = e->ReactEvent.Form.currentTarget##value;
      setState(_ => value);
      ();
    });
  <div>
    <input placeholder={j|Search gifs…|j} autoFocus=true value=state onChange />
    <GifList searchTerm=state />
  </div>;
};
