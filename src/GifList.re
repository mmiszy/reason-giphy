type state = {
  isLoading: bool,
  response: option(GiphyApi.gifsResponse),
  error: option(Js.Promise.error),
};

let initialState = {isLoading: false, response: None, error: None};

type action =
  | FetchStarted
  | FetchSuccessful(GiphyApi.gifsResponse)
  | FetchFailed(Js.Promise.error);

let gifsListReducer = (state, action) => {
  switch (action) {
  | FetchStarted => {...state, isLoading: true, error: None}
  | FetchSuccessful(gifs) => {isLoading: false, error: None, response: Some(gifs)}
  | FetchFailed(err) => {isLoading: false, error: Some(err), response: None}
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
  let (state, dispatch) = React.useReducer(gifsListReducer, initialState);

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
    <div> {React.string("There was an error!")} </div>;
  | {response: Some(gifs)} =>
    gifs
    |> Array.map((gif: GiphyApi.singleGif) =>
         <li key={gif.url}>
           <video width={gif.width} height={gif.height} src={gif.mp4} autoPlay=true loop=true />
         </li>
       )
    |> React.array
  | _ => React.null
  };
};
