import tensorflow as tf
import os


def get_model_folders(directory):
    """
    Add each subdirectory in /models/ to a list and return that list.
    Assumption: only subfolders with valid neural network models are present under /models/.
    """
    model_folders = []
    items = os.listdir(directory)

    for item in items:
        item_path = os.path.join(directory, item)
        if os.path.isdir(item_path):
            model_folders.append(item)

    return model_folders


def load_models(models):
    loaded_models = []
    for model in models:
        loaded_models.append(tf.saved_model.load(model))

    return loaded_models


if __name__ == '__main__':
    cwd = os.path.dirname(os.path.abspath(__file__))

    # All models should be stored in subfolders of /src/model-loader/models/
    directory = os.path.join(cwd, 'models')
    model_subfolders = get_model_folders(directory)

    # Assumption/requirement: model name is of type .pb and has the same name as the parent folder
    # model_names = []
    # for folder in model_subfolders:
    #     model_names.append(folder + '.pb')

    # Create list of models with the full path to each stored in a list.
    models = []
    for i in range(len(model_subfolders)):
        models.append(os.path.join(
            # directory, model_subfolders[i], model_names[i]))
            directory, model_subfolders[i]))

    found_models = load_models(models)
    print(f'Successfully loaded {len(found_models)} model(s)')

    # for folder in model_subfolders:
    #    print(folder)
