type state = {
  isLoading: bool,
  response: option(GiphyApi.gifsResponse),
  error: option(Js.Promise.error),
};

let initialState = {isLoading: false, response: None, error: None};

type action =
  | FetchStarted
  | FetchFailed(Js.Promise.error)
  | FetchSuccessful(GiphyApi.gifsResponse);

let gisListReducer = (state, action) => {
  switch (action) {
  | FetchStarted => {...state, isLoading: true, error: None}
  | FetchFailed(err) => {isLoading: false, response: None, error: Some(err)}
  | FetchSuccessful(gifs) => {isLoading: false, response: Some(gifs), error: None}
  };
};

let fetchGifsActionCreator = (dispatch, searchTerm) => {
  dispatch(FetchStarted);
  Js.Promise.(
    GiphyApi.searchGifs(searchTerm)
    |> then_(gifs => {
         dispatch(FetchSuccessful(gifs));
         resolve();
       })
    |> catch(err => {
         dispatch(FetchFailed(err));
         resolve();
       })
  )
  |> ignore;
};

[@react.component]
let make = (~searchTerm: string) => {
  let (state, dispatch) = React.useReducer(gisListReducer, initialState);

  React.useEffect1(
    () => {
      fetchGifsActionCreator(dispatch, searchTerm);
      None;
    },
    [|searchTerm|],
  );

  switch (state) {
  | {error: Some(err)} =>
    Js.log(err);
    React.null;
  | {response: Some(gifs)} =>
    gifs
    |> Array.map((gif: GiphyApi.singleGif) =>
         <li key={gif.url}>
           <video width={gif.width} height={gif.height} src={gif.mp4} autoPlay=true loop=true />
         </li>
       )
    |> ReasonReact.array
  | _ => React.null
  };
};
